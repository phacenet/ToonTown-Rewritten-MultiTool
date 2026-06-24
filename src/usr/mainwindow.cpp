#include "mainwindow.hpp"
#include "direct_inputs.hpp"
#include "file_detect.hpp"
#include "ttr_api_reqs.hpp"
#include "ui_mainwindow.h"
#include "encryption.hpp"
#include "adblocker.cpp"
#include "qt_incs.hpp"

#include <thread>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sodium/crypto_secretbox.h>
#include <string>


enum class PageIndex : uint8_t 
{
    pageLogin,
    pageAppSelect,
    pageToonHQAutoToonSelect, pageToonHQConnected,
    pageClientLaunch,
    pageDualToon,
    pageInvasionTracker,
    pageDoodleTraining,
    pageToonHQWebsiteView
};


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) 
{
    ui->setupUi(this);
    ui->titleBarFrame->installEventFilter(this);
    ui->toonListWidget->viewport()->installEventFilter(this);

    //Global font
    int id = QFontDatabase::addApplicationFont("config/fonts/impress-bt.ttf");
    QString loadedFont;
    if(id != -1 && !QFontDatabase::applicationFontFamilies(id).isEmpty())
        loadedFont = QFontDatabase::applicationFontFamilies(id).at(0);
    else
        loadedFont = "Arial"; //fallback if font file is missing from deployment
    m_ttrFontSmall = QFont(loadedFont, 12);
    m_ttrFont = QFont(loadedFont, 16);
    m_ttrFontLarge = QFont(loadedFont, 18);
    m_ttrFontXL = QFont(loadedFont, 22);
    
    //Window params
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setFixedSize(QSize(810, 600));
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowIcon(QIcon("config/icons/app_icon.png"));
    QSystemTrayIcon* trayIcon(new QSystemTrayIcon(QIcon("config/icons/app_icon.png")));
    trayIcon->show();
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x,y);

    // set fonts for labels/buttons as well as cursor
    ui->username_label->setFont(m_ttrFontLarge);
    ui->username_input->setFont(m_ttrFontLarge);
    ui->password_label->setFont(m_ttrFontLarge);
    ui->password_input->setFont(m_ttrFontLarge);
    ui->xBtn->setFont(m_ttrFont);
    ui->minBtn->setFont(m_ttrFontXL);
    ui->homeBtn->setFont(m_ttrFontLarge);
    ui->statusLabel->setFont(m_ttrFontLarge);
    ui->storeLoginCheckbox->setFont(m_ttrFontLarge);
    ui->submitBtn->setFont(m_ttrFontLarge);

    ui->homeBtn->setCursor(Qt::PointingHandCursor);
    ui->xBtn->setCursor(Qt::PointingHandCursor);
    ui->minBtn->setCursor(Qt::PointingHandCursor);
    ui->storeLoginCheckbox->setCursor(Qt::PointingHandCursor);

    //trying to fix Win32 version toon image fetching not always fetching all toon images
    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    sslConfig.setProtocol(QSsl::TlsV1_2OrLater);
    QSslConfiguration::setDefaultConfiguration(sslConfig);


    //------------------------------------------------------------------------------------------
    //login page
    //------------------------------------------------------------------------------------------
    //cursor focus
    ui->username_input->setFocus();

    // Always set placeholder text first so it shows on every path —
    // including fresh installs where no credential file exists yet.
    // If credentials are found below, setText overrides the placeholder normally.
    ui->username_input->setPlaceholderText("Enter your username...");
    ui->password_input->setPlaceholderText("Enter your password...");

    // Load saved username and password from bin if stored
    try
    {
        if(enc::readState_fromFile())
        {
            ui->storeLoginCheckbox->toggle();
            m_dontStoreCreds = true;
        }
        else
        {
            enc::ToonHQLogin fetchedCreds = enc::fetch_creds(m_loginsPath.keyPath, m_loginsPath.credPath);
            if(!fetchedCreds.username.empty() && !fetchedCreds.password.empty())
            {
                ui->username_input->setText(QString::fromStdString(fetchedCreds.username));
                ui->password_input->setText(QString::fromStdString(fetchedCreds.password));
            }
        }
    }
    catch(const std::exception& e)
    {
        // Credential file is corrupt or key mismatch — reset gracefully.
        // Placeholder text is already set above so no need to repeat it here.
        ui->statusLabel->setStyleSheet("color: red;");
        ui->statusLabel->setText(QString("Credential load error: ") + e.what());
    }

    //Button connects
    connect(ui->xBtn, &QPushButton::clicked, this, &MainWindow::on_xBtnClicked);
    connect(ui->minBtn, &QPushButton::clicked, this, &QWidget::showMinimized);
    connect(ui->submitBtn, &QPushButton::clicked, this, [this]()
        {
            submitPressed(ui->username_input->text().toStdString(), ui->password_input->text().toStdString());
        });
    
    //Make "return" trigger submit button if inside password lineEntry
    connect(ui->password_input, &QLineEdit::returnPressed, this, &MainWindow::attemptLogin);

    //Update statusbar on login success/fail
    connect(this, &MainWindow::loginAuthenticated, this, [this]()
        {
            ui->statusLabel->setStyleSheet("color: #17fc03");
            ui->statusLabel->setText("Login success");
            ui->stackedWidget->setCurrentIndex((int)PageIndex::pageAppSelect);
            populateToonList();
        });
    connect(this, &MainWindow::loginFailed, this, [this]()
        {   
            ui->statusLabel->setStyleSheet("color: red");
            ui->statusLabel->setText("Login Failed");
        });
    //dont store credentials if clicked
    connect(ui->storeLoginCheckbox, &QCheckBox::toggled, this, [this](bool checked){ m_dontStoreCreds = checked;});
    connect(ui->homeBtn, &QPushButton::pressed, this, [this]()
            {
                if(ui->stackedWidget->currentIndex() == (int)PageIndex::pageInvasionTracker)
                {
                    m_invasionPollTimer->stop();
                    m_invasionTickTimer->stop();
                }

                if(ui->stackedWidget->currentIndex() != (int)PageIndex::pageLogin)
                    ui->stackedWidget->setCurrentIndex((int)PageIndex::pageAppSelect);
            });
    //------------------------------------------------------------------------------------------


    //------------------------------------------------------------------------------------------
    //AppSelect Page
    //------------------------------------------------------------------------------------------
    connect(ui->AutoGroupSelectBtn, &QPushButton::clicked, this, [this](){
            ui->stackedWidget->setCurrentIndex((int)PageIndex::pageToonHQAutoToonSelect);
            });

    connect(ui->LaunchTTBtn, &QPushButton::clicked, this, [this](){
        ui->stackedWidget->setCurrentIndex((int)PageIndex::pageClientLaunch);
        });

    connect(ui->DualToonContBtn, &QPushButton::pressed, this, [this](){ui->stackedWidget->setCurrentIndex( (int)PageIndex::pageDualToon); });
    connect(ui->DoodleBtn, &QPushButton::pressed, this, [this](){ ui->stackedWidget->setCurrentIndex( (int)PageIndex::pageDoodleTraining); });
    //------------------------------------------------------------------------------------------
    

    //------------------------------------------------------------------------------------------
    //Auto group select PageS
    //------------------------------------------------------------------------------------------
    connect(ui->toonListWidget, &QListWidget::itemClicked, this, [this](QListWidgetItem* item)
        {
            int row = ui->toonListWidget->row(item);
            const auto& toon = m_toonTown_loginStruct.toonlist[row];
            ui->toonListWidget->clearSelection();
        });

    //connected toon page
    ui->connectedInfoLabel->setFont(m_ttrFontXL);
    connect(ui->disconnectToonBtn, &QPushButton::pressed, this, [this]()
            {
                ui->connectedInfoLabel->setText("Disconnecting...");
                ui->connectedInfoLabel->setStyleSheet("color: #fa6e75;");
                ui->connectedInfoLabel->setFont(m_ttrFontXL);
                ui->connectedInfoLabel->repaint();
                ui->connectedInfoLabel->setStyleSheet("color: white;");

                if (m_sioClient)
                {
                    m_sioClient->sync_close();
                    delete m_sioClient;
                    m_sioClient = nullptr;
                }
                if (m_resubscribeTimer)
                    m_resubscribeTimer->stop();

                for (auto &toon : m_toonTown_loginStruct.toonlist)
                {
                    if (toon.ToonID == m_connectedToon.ToonID)
                    {
                        toon.activeConnection = false;
                        break;
                    }
                }
                m_connectedToon.activeConnection = false;
                ui->connectedInfoLabel->setText("Disconnected");
                ui->connectedToonLabel->clear();
            });
    //------------------------------------------------------------------------------------------
   

    //------------------------------------------------------------------------------------------
    // Launch game pages
    m_numCreds = enc::read_numCreds();
    setFonts();
    setNoFocusItems();
    if(std::filesystem::exists("config/Doodle/labels.txt"))
        setLabelBoxes();

    //Client store 1
    if(m_numCreds == 0)
    {
        state_freshLoad(1);
        state_freshLoad(2);
        state_freshLoad(3);
    }
    else
        state_registeredLoad(m_numCreds);
    
     connect(ui->addClient_btn1, &QPushButton::pressed, this, [this](){ state_addClientPressed(1); });
     connect(ui->save_btn1, &QPushButton::pressed, this, [this](){ state_saveButtonPressed(1); });
     connect(ui->edit_btn1, &QPushButton::pressed, this, [this](){ state_editButtonPressed(1); });
     connect(ui->remove_bt1, &QPushButton::pressed, this, [this](){ state_removeButtonPressed(1); });
     connect(ui->save_btn1_noInc, &QPushButton::pressed, this, [this](){ state_saveNoIncButtonPressed(1); });
     connect(ui->launch_btn1, &QPushButton::pressed, this, [this](){ state_launchButton(1); });

     connect(ui->addClient_btn2, &QPushButton::pressed, this, [this](){ state_addClientPressed(2); });
     connect(ui->save_btn2, &QPushButton::pressed, this, [this](){ state_saveButtonPressed(2); });
     connect(ui->edit_btn2, &QPushButton::pressed, this, [this](){ state_editButtonPressed(2); });
     connect(ui->remove_bt2, &QPushButton::pressed, this, [this](){ state_removeButtonPressed(2); });
     connect(ui->save_btn2_noInc, &QPushButton::pressed, this, [this](){ state_saveNoIncButtonPressed(2); });
     connect(ui->launch_btn2, &QPushButton::pressed, this, [this](){ state_launchButton(2); });
                    
     connect(ui->addClient_btn3, &QPushButton::pressed, this, [this](){ state_addClientPressed(3); });
     connect(ui->save_btn3, &QPushButton::pressed, this, [this](){ state_saveButtonPressed(3); });
     connect(ui->edit_btn3, &QPushButton::pressed, this, [this](){ state_editButtonPressed(3); });
     connect(ui->remove_bt3, &QPushButton::pressed, this, [this](){ state_removeButtonPressed(3); });
     connect(ui->save_btn3_noInc, &QPushButton::pressed, this, [this](){ state_saveNoIncButtonPressed(3); });
     connect(ui->launch_btn3, &QPushButton::pressed, this, [this](){ state_launchButton(3); });

     connect(ui->manual_loc_btnEDIT1, &QPushButton::pressed, this, [this]()
             {
                QString filepath = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("All Files (*);; Executable Files (*.exe)"));
                if(!filepath.isEmpty())
                    ui->fileLocation_input1->setText(filepath);
             });
     connect(ui->manual_loc_btnEDIT2, &QPushButton::pressed, this, [this]()
             {
                QString filepath = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("All Files (*);; Executable Files (*.exe)"));
                if(!filepath.isEmpty())
                    ui->fileLocation_input2->setText(filepath);
             });
     connect(ui->manual_loc_btnEDIT3, &QPushButton::pressed, this, [this]()
             {
                QString filepath = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("All Files (*);; Executable Files (*.exe)"));
                if(!filepath.isEmpty())
                    ui->fileLocation_input3->setText(filepath);
             });
    //------------------------------------------------------------------------------------------
    
    //------------------------------------------------------------------------------------------
    // Dual toon page
    //------------------------------------------------------------------------------------------
    connect(ui->start_arrowKeysBtn, &QPushButton::pressed, this, [this]()
            {
                if(m_dualToonActiveARROWS) return;
                m_dualToonActiveARROWS = true;

                if(m_dualToonStatus.wasd == true)
                    m_dualToonStatus = {.none = false, .wasd = false, .arrow_keys = false, .both = true};
                else
                    m_dualToonStatus = {.none = false, .arrow_keys = true};
                
                set_whichRunningLabel();
                
                m_targetARROWKEYSWindow = dir_inp::get_window_via_click();
                    m_dualToonThreadArrows = std::thread([this]()
                    {
                        // all keys we care about
                        std::vector<unsigned int> keys = {
                            dir_inp::KEY_UP, dir_inp::KEY_DOWN,
                            dir_inp::KEY_LEFT, dir_inp::KEY_RIGHT,
                            dir_inp::KEY_SPACE, dir_inp::KEY_ESCAPE,
                            dir_inp::KEY_ALT_L, dir_inp::KEY_ALT_R,
                            dir_inp::KEY_HOME, dir_inp::KEY_END
                        };

                        // track previous state for each key so we detect edges
                        std::vector<bool> prev(keys.size(), false);

                        while(m_dualToonActiveARROWS)
                        {
                            auto states = dir_inp::poll_keys(keys);

                            for(size_t i = 0; i < keys.size(); i++)
                            {
                                if(m_wasdPaused && keys[i] == dir_inp::KEY_SPACE)
                                {
                                    if(prev[i])
                                    {
                                        dir_inp::send_key_to_window(m_targetARROWKEYSWindow, keys[i], false);
                                        prev[i] = false;
                                    }
                                    continue;
                                }

                                if(states[i] && !prev[i])
                                    dir_inp::send_key_to_window(m_targetARROWKEYSWindow, keys[i], true);
                                else if(!states[i] && prev[i])
                                    dir_inp::send_key_to_window(m_targetARROWKEYSWindow, keys[i], false);

                                prev[i] = states[i];
                            }
                            std::this_thread::sleep_for(std::chrono::milliseconds(8));
                        }

                        // release any keys still held when stopping
                        for(size_t i = 0; i < keys.size(); i++)
                        {
                            if(prev[i])
                                dir_inp::send_key_to_window(m_targetARROWKEYSWindow, keys[i], false);
                        }
                    });
            });
    connect(ui->stop_dualBtn, &QPushButton::pressed, this, [this]()
            {
                m_dualToonActiveWASD = false;
                m_dualToonActiveARROWS = false;
                if(m_dualToonThreadWASD.joinable())
                    m_dualToonThreadWASD.join();
                if(m_dualToonThreadArrows.joinable())
                    m_dualToonThreadArrows.join();
                m_dualToonStatus = {.none = true, .wasd = false, .arrow_keys = false, .both = false};
                set_whichRunningLabel();
                ui->typingLabel->setText("");
            });

        connect(ui->start_WASDBtn, &QPushButton::clicked, this, [this]()
        {
            if(m_dualToonActiveWASD) return;
            m_dualToonActiveWASD = true;

            if(m_dualToonStatus.arrow_keys == true)
                m_dualToonStatus = {.none = false, .wasd = false, .arrow_keys = false, .both = true};
            else
                m_dualToonStatus = {.none = false, .wasd = true};

            set_whichRunningLabel();

            m_targetWASDWindow = dir_inp::get_window_via_click();
            m_dualToonThreadWASD = std::thread([this]()
            {
                std::vector<unsigned int> keys = {
                    dir_inp::KEY_w, dir_inp::KEY_a,
                    dir_inp::KEY_s, dir_inp::KEY_d,
                    dir_inp::KEY_SPACE, dir_inp::KEY_ESCAPE,
                    dir_inp::KEY_ALT_L, dir_inp::KEY_ALT_R,
                    dir_inp::KEY_HOME, dir_inp::KEY_END
                };
                std::vector<bool> prev(keys.size(), false);

                bool enterPrev = false;

                while(m_dualToonActiveWASD)
                {
                    bool enterNow = dir_inp::is_key_pressed(dir_inp::KEY_RETURN);
                    if(enterNow && !enterPrev)
                    {
                        m_wasdPaused = !m_wasdPaused;
                        QMetaObject::invokeMethod(this, [this]()
                                {
                                    if(m_wasdPaused)
                                    {
                                        ui->typingLabel->setText("Typing mode: WASD paused");
                                        ui->typingLabel->setStyleSheet("color: red;");
                                    }
                                    else
                                    {
                                        ui->typingLabel->setText("Typing mode: Off");
                                        ui->typingLabel->setStyleSheet("color: green;");
                                    }
                                }, Qt::QueuedConnection);
                    }
                    enterPrev = enterNow;

                    if(!m_wasdPaused)
                    {
                        auto states = dir_inp::poll_keys(keys);
                        for(size_t i = 0; i < keys.size(); i++)
                        {
                            if(states[i] && !prev[i])
                                dir_inp::send_key_to_window(m_targetWASDWindow, keys[i], true);
                            else if(!states[i] && prev[i])
                                dir_inp::send_key_to_window(m_targetWASDWindow, keys[i], false);
                            prev[i] = states[i];
                        }
                    }
                    else
                    {
                        for(size_t i = 0; i < keys.size(); i++)
                        {
                            if(prev[i])
                            {
                                dir_inp::send_key_to_window(m_targetWASDWindow, keys[i], false);
                                prev[i] = false;
                            }
                        }
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(8));
                }
                for(size_t i = 0; i < keys.size(); i++)
                    if(prev[i])
                        dir_inp::send_key_to_window(m_targetWASDWindow, keys[i], false);
            });
        });
    //------------------------------------------------------------------------------------------

    //------------------------------------------------------------------------------------------
    //Doodle training page
    //------------------------------------------------------------------------------------------
        connect(ui->start_trick1Btn, &QPushButton::pressed, this, [this]()
            {
                std::vector<ClickStep> click_steps = m_doodleTrainStartSteps;
                click_steps.push_back(ClickStep{312, 58, 1500}); //trick 1
                doodleTrain(click_steps);
                if(ui->labelBox->currentText() != "Optional Label")
                    ui->current_trickLabel->setText("Currently training: " + ui->labelBox->currentText());
                else
                    ui->current_trickLabel->setText("Currently training: Trick 1");
            });
        connect(ui->start_trick2Btn, &QPushButton::pressed, this, [this]()
            {
                std::vector<ClickStep> click_steps = m_doodleTrainStartSteps;
                click_steps.push_back(ClickStep{302, 78, 1500}); //trick 2
                doodleTrain(click_steps);
                if(ui->labelBox_2->currentText() != "Optional Label")
                    ui->current_trickLabel->setText("Currently training: " + ui->labelBox_2->currentText());
                else
                    ui->current_trickLabel->setText("Currently training: Trick 2");
            });
        connect(ui->start_trick3Btn, &QPushButton::pressed, this, [this]()
            {
                std::vector<ClickStep> click_steps = m_doodleTrainStartSteps;
                click_steps.push_back(ClickStep{308, 100, 1500}); //trick 3
                doodleTrain(click_steps);
                if(ui->labelBox_3->currentText() != "Optional Label")
                    ui->current_trickLabel->setText("Currently training: " + ui->labelBox_3->currentText());
                else
                    ui->current_trickLabel->setText("Currently training: Trick 2");
            });
        connect(ui->start_trick4Btn, &QPushButton::pressed, this, [this]()
            {
                std::vector<ClickStep> click_steps = m_doodleTrainStartSteps;
                click_steps.push_back(ClickStep{299, 119, 1500}); //trick 4
                doodleTrain(click_steps);
                if(ui->labelBox_3->currentText() != "Optional Label")
                    ui->current_trickLabel->setText("Currently training: " + ui->labelBox_3->currentText());
                else
                    ui->current_trickLabel->setText("Currently training: Trick 2");
            });

    connect(ui->stop_trainingBtn, &QPushButton::pressed, this, [this]()
            {
                m_doodleTrainingActive = false;
                if(m_doodleTrainThread.joinable())
                    m_doodleTrainThread.join();
                ui->current_trickLabel->setText("Not currently training");
            });
    connect(ui->grab_coordsBtn, &QPushButton::pressed, this, [this]()
            {
                long window_id = dir_inp::get_window_via_click();

                if(window_id == 0) return;
                std::this_thread::sleep_for(std::chrono::seconds(3));
                 auto pos = dir_inp::get_mouse_pos_in_window(window_id);
                 std::cout << "local coords: " << pos.x << ", " << pos.y << '\n';
            });
                /*
                long window_id = dir_inp::get_window_via_click();
                std::cout << "retrieved window_id as: " << window_id << '\n';

                if(window_id == 0) return;

                // give yourself time to click a different window
                std::this_thread::sleep_for(std::chrono::seconds(3));
               
                 auto pos = dir_inp::get_mouse_pos_in_window(window_id);
                 std::cout << "local coords: " << pos.x << ", " << pos.y << '\n';

                 //106,59 open speedchat
                 //317, 147 open pets
                 //542, 144 open tricks
                 //723, 146 trick 1
                 //718, 186 trick 2
                 //739, 245 trick 3
                 */
    //------------------------------------------------------------------------------------------
    
    //------------------------------------------------------------------------------------------
    //Invasion Tracker page
    //------------------------------------------------------------------------------------------
    m_invasionPollTimer = new QTimer(this);
    m_invasionTickTimer = new QTimer(this);

    connect(m_invasionPollTimer, &QTimer::timeout, this, &MainWindow::pollInvasions);
    connect(m_invasionTickTimer, &QTimer::timeout, this, [this](){ updateInvasionTimers(); });

    //start polling when user navigates to the page
    connect(ui->InvasionBtn, &QPushButton::pressed, this, [this]()
        {
            ui->stackedWidget->setCurrentIndex((int)PageIndex::pageInvasionTracker);
            m_invasionPollTimer->start(10000); //poll every 10s
            m_invasionTickTimer->start(1000); //tick every 1s
            QTimer::singleShot(0, this, &MainWindow::pollInvasions);
        });

    ui->invasionListWidget->setFont(m_ttrFontLarge);
    ui->invasionListWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->invasionListWidget->setFocusPolicy(Qt::NoFocus);
    ui->invasionListWidget->setSpacing(0);
    ui->invasionListWidget->setStyleSheet(R"(
        QListWidget {
            background: transparent;
            border: none;
        }
        QListWidget::item {
            padding: 6px;
            border-bottom: 1px solid rgba(255, 255, 255, 30);
        }
    )");

    m_hotkeyThread = std::thread([this]()
    {
        bool prevF1 = false;
        while(m_hotkeyActive)
        {
            bool nowF1 = dir_inp::is_key_pressed(dir_inp::KEY_F1);
            if(nowF1 && !prevF1)
            {
                QMetaObject::invokeMethod(this, [this]()
                {
                    if(isActiveWindow() && !isMinimized())
                    {
                        showMinimized();
                    }
                    else
                    {
                        show();
                        setWindowState((windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
                        raise();
                        
                        #ifdef __linux__
                        QProcess::startDetached("wmctrl", {"-i", "-a", QString::number(winId())});
                        #endif
                        
                        activateWindow();

                        ui->stackedWidget->setCurrentIndex((int)PageIndex::pageInvasionTracker);
                        m_invasionPollTimer->start(10000); //poll every 10s
                        m_invasionTickTimer->start(1000);
                        QTimer::singleShot(0, this, &MainWindow::pollInvasions);
                    }
                }, Qt::QueuedConnection);
            }
            prevF1 = nowF1;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    });
    //------------------------------------------------------------------------------------------

    //------------------------------------------------------------------------------------------
    //Website View Page
    //------------------------------------------------------------------------------------------
    connect(ui->ToonHQWebBtn, &QPushButton::clicked, this, [this]()
    {
        ui->stackedWidget->setCurrentIndex((int)PageIndex::pageToonHQWebsiteView);
if(!m_browser)
{
    auto* profile = new QWebEngineProfile("toonhq", this);
    profile->setPersistentStoragePath(
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/webengine");
    profile->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);

    // temporarily comment out blocker
    auto* blocker = new AdBlocker(this);
    profile->setUrlRequestInterceptor(blocker);

    auto* page = new QWebEnginePage(profile, this);
    m_browser = new QWebEngineView(ui->ToonHQWebsitePage);
    m_browser->setPage(page);
    m_browser->setGeometry(QRect(20, 60, 781, 531));
    m_browser->setUrl(QUrl("https://toonhq.org/groups/"));
    m_browser->show();  // force show — might be needed since parent page isn't visible yet
}
    });
    //------------------------------------------------------------------------------------------

}

//destructor ~
MainWindow::~MainWindow() {
    m_dualToonActiveWASD = false;
    m_dualToonActiveARROWS = false;
    m_hotkeyActive = false;

    if(m_dualToonThreadWASD.joinable())
        m_dualToonThreadWASD.join();
    if(m_dualToonThreadArrows.joinable())
        m_dualToonThreadArrows.join();
    if(m_hotkeyThread.joinable())
        m_hotkeyThread.join();
    
    //set label boxes
    storeLabelBoxes();
    delete ui;
}

//------------------------------------------------------------------------------------------
//protected: 
//------------------------------------------------------------------------------------------
void MainWindow::mousePressEvent(QMouseEvent* event)
{
    m_dragging = true;
    m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if(m_dragging)
    {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

// titlebar drag logic
bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    if(object == ui->titleBarFrame && event->type() == QEvent::MouseButtonRelease)
    {
        m_dragging = false;
        return true;
    }

    if(object == ui->toonListWidget->viewport() && event->type() == QEvent::Resize)
        updateToonRowWidth();

    return false;
}


//------------------------------------------------------------------------------------------


//xBtn
void MainWindow::on_xBtnClicked() {close();}

// password line edit "enter" causes submit button to fire
void MainWindow::attemptLogin()
{
    ui->submitBtn->animateClick();
}

void MainWindow::submitPressed(const std::string& uName, const std::string& pWord)
{
    std::cout << "Submit button was pressed\n";

    // Disable the button for the duration of the request so double-clicks
    // can't queue a second login attempt.
    ui->submitBtn->setEnabled(false);
    ui->statusLabel->setStyleSheet("color: white;");
    ui->statusLabel->setText("Logging in...");

    // retrieve_csrftoken() and login_request() are both blocking CURL calls.
    // Calling them directly on the main thread blocks Qt's event loop, which
    // causes the "exception thrown from an event handler" / QWidget assert on
    // Windows (Qt catches the propagating exception from inside the signal
    // dispatch and re-throws, which terminates). Move the work off-thread and
    // marshal the result back via QMetaObject::invokeMethod.
    std::thread([this, uName, pWord]()
    {
        try
        {
            std::string csrftoken = ttr::retrieve_csrftoken();
            std::optional<ttr::ToonHQLoginResult> login_result =
                ttr::login_request(csrftoken, uName, pWord);

            QMetaObject::invokeMethod(this, [this, uName, pWord, csrftoken, login_result]()
            {
                ui->submitBtn->setEnabled(true);

                if(login_result)
                {
                    m_orig_csrftoken = csrftoken;
                    m_toonTown_loginStruct = *login_result;

                    if(m_dontStoreCreds)
                    {
                        enc::storeState_toFile();
                        std::string credpath = "config/ToonHQLogin/credentials.bin";
                        if(std::filesystem::exists(credpath))
                            std::filesystem::remove(credpath);
                        Q_EMIT loginAuthenticated();
                    }
                    else
                    {
                        std::string user_data = uName + '\n' + pWord;
                        unsigned char key[crypto_secretbox_KEYBYTES];
                        enc::load_keyfile(m_loginsPath.keyPath, key);
                        enc::encrypt_to_file(user_data, m_loginsPath.credPath, key);
                        enc::delete_storeState();
                        Q_EMIT loginAuthenticated();
                    }
                }
                else
                {
                    Q_EMIT loginFailed();
                }
            }, Qt::QueuedConnection);
        }
        catch(const std::exception& e)
        {
            // Capture message by value so it's safe to use in the lambda
            // after the catch block unwinds.
            std::string msg = e.what();
            QMetaObject::invokeMethod(this, [this, msg]()
            {
                ui->submitBtn->setEnabled(true);
                ui->statusLabel->setStyleSheet("color: red;");
                ui->statusLabel->setText(QString("Login error: ") + QString::fromStdString(msg));
            }, Qt::QueuedConnection);
        }
    }).detach();
}

void MainWindow::populateToonList()
{
    ui->toonListWidget->clear();
    ui->toonListWidget->setCursor(Qt::PointingHandCursor);
    ui->toonListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->toonListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->toonListWidget->setMouseTracking(true);
    ui->toonListWidget->setSpacing(6);
    ui->toonListWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->toonListWidget->setFocusPolicy(Qt::NoFocus);
    ui->toonListWidget->setStyleSheet(R"(
    QListWidget {
        border: none;
        background: transparent;
    }
    )");

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    //non const to modify active connection status
    for(auto& Toon : m_toonTown_loginStruct.toonlist)
    {
        auto* item = new QListWidgetItem();

        auto* rowBtn = new QPushButton;
        rowBtn->setFlat(true);
        rowBtn->setMinimumHeight(72);
        rowBtn->setText("");
        rowBtn->setCursor(Qt::PointingHandCursor);
        rowBtn->setStyleSheet(R"(
            QPushButton {
                text-align: left;
                background-color: qlineargradient(
    		        spread:pad,
    		        x1:0.5, y1:0,
    		        x2:0.5, y2:1,
    		        stop:0 #008BF8,
    		        stop:1 #00D3F8
	            );
                border: 1px solid transparent;
                border-radius: 12px;
                padding: 2px;

            }
            QPushButton:hover {
                background-color: qlineargradient(
    		        spread:pad,
    		        x1:0.5, y1:0,
    		        x2:0.5, y2:1,
    		        stop:0 #5f86e0,
    		        stop:1 #295ed5
	            );
            }
            QPushButton:pressed {
                background-color: rgba(23, 252, 3, 60);
            }
        )");

        auto* layout = new QHBoxLayout(rowBtn);
        layout->setContentsMargins(8, 4, 8, 4);
        layout->setSpacing(8);

        QLabel* image = new QLabel;
        QString tmp = QString::fromStdString(Toon.ToonName + " | Laff: " + std::to_string(Toon.ToonLaff) + " | Game: " +
                (Toon.game == 1 ? "Toontown Rewritten" : "Corporate Clash"));
        QLabel* name = new QLabel(tmp);
        name->setFont(m_ttrFontLarge);
        name->setStyleSheet("color: white;");
        image->setFixedSize(60, 60);

        image->setAttribute(Qt::WA_TransparentForMouseEvents, true); 
        name->setAttribute(Qt::WA_TransparentForMouseEvents, true);

        // download image 
        QNetworkRequest req(QUrl(QString::fromStdString(Toon.ToonPhotoURL)));
        QNetworkReply* reply = manager->get(req);
        connect(reply, &QNetworkReply::finished, this, [=]()
            {
                if(reply->error() != QNetworkReply::NoError)
                {
                    qDebug() << "Network error: " << reply->errorString();
                    reply->deleteLater();
                    return;
                }
                QByteArray data = reply->readAll();
                QPixmap pix;
                pix.loadFromData(data);
                image->setPixmap(pix.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                reply->deleteLater();
            });

        layout->addWidget(image);
        layout->addWidget(name);
        layout->addStretch();
        rowBtn->setLayout(layout);

        item->setSizeHint(QSize(100, rowBtn->minimumHeight()));

        connect(rowBtn, &QPushButton::clicked, this, [this, &Toon]()
            {
                // selection logic here, e.g.:
                Toon.activeConnection = true;
                m_connectedToon = Toon;
        
                //actual connection logic
                startBoarding();

                //load images
                loadSelectedToonImg(QString::fromStdString(m_connectedToon.ToonPhotoURL), ui->connectedToonLabel, ui->connectedInfoLabel);
                ui->stackedWidget->setCurrentIndex((int)PageIndex::pageToonHQConnected);
            });

        ui->toonListWidget->addItem(item);
        ui->toonListWidget->setItemWidget(item, rowBtn);
        updateToonRowWidth();
        }

}

void MainWindow::updateToonRowWidth()
{
    int width = ui->toonListWidget->viewport()->width() - 10;

    for(int i = 0; i < ui->toonListWidget->count(); ++i)
    {
        QListWidgetItem* item = ui->toonListWidget->item(i);
        QSize hint = item->sizeHint();
        hint.setWidth(width);
        item->setSizeHint(hint);
    }
}

void MainWindow::loadSelectedToonImg(const QString& url, QLabel* label, QLabel* labelInfo)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkReply* reply = manager->get(QNetworkRequest(QUrl(url)));

    label->setFixedSize(80, 80);
    label->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    QString infoLabelText(QString::fromStdString(m_connectedToon.ToonName + " is connected"));
    labelInfo->setText(infoLabelText);

    connect(reply, &QNetworkReply::finished, this, [reply, label]()
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            QPixmap pix;
            pix.loadFromData(reply->readAll());
            label->setPixmap(pix.scaled(label->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
        }
        else
        {
            qDebug() << "Network error: " << reply->errorString();
        }
        reply->deleteLater();
    });
}

void MainWindow::startBoarding()
{
    m_sioClient = ttr::link_information(m_toonTown_loginStruct, m_connectedToon, [this](bool success)
            {
                QMetaObject::invokeMethod(this, [this, success]()
                {
                    if(!success)
                    {
                        ui->connectedToonLabel->clear();
                        ui->connectedInfoLabel->setText(QString::fromStdString(m_connectedToon.ToonName) + ": couldn't find that toon");
                        ui->connectedInfoLabel->setFont(m_ttrFont);
                        if (m_resubscribeTimer)
                            m_resubscribeTimer->stop();
                    }
                }, Qt::QueuedConnection);
            });

    if (!m_resubscribeTimer)
    {
        m_resubscribeTimer = new QTimer(this);
        connect(m_resubscribeTimer, &QTimer::timeout, this, [this]()
        {
            if (m_sioClient)
            {
                std::string sid = m_sioClient->get_sessionid();
                ttr::subscribe_boarding(m_toonTown_loginStruct, m_connectedToon, sid);
            }
        });
        m_resubscribeTimer->start(240000); // re-subscribe every 4 minutes
    }
}



void MainWindow::state_freshLoad(uint8_t which_one)
{
    switch(which_one)
    {
        case 1:
        {
            ui->unameInput1->setPlaceholderText("Enter your Toontown Username...");
            ui->pwordInput1->setPlaceholderText("Enter your Toontown Password...");
            ui->aliasInput1->setPlaceholderText("Enter an alias (optional)");
            ui->fileLocation_input1->setPlaceholderText("(Optional) Enter alternative installation path");
            ui->uname_label_1->hide();
            ui->unameInput1->hide();
            ui->pword_label_1->hide();
            ui->pwordInput1->hide();
            ui->alias_label_1->hide();
            ui->aliasInput1->hide();
            ui->launch_label1->hide();
            ui->edit_btn1->hide();
            ui->save_btn1->hide();
            ui->save_btn1_noInc->hide();
            ui->remove_bt1->hide();
            ui->status_label_1->hide();
            ui->launch_btn1->hide();
            hide_file_location(1);

            ui->addClient_btn1->show();
            ui->addClient_label1->show();
            break;
        }
        case 2:
        {
            ui->unameInput2->setPlaceholderText("Enter your Toontown Username...");
            ui->pwordInput2->setPlaceholderText("Enter your Toontown Password...");
            ui->aliasInput2->setPlaceholderText("Enter an alias (optional)");
            ui->fileLocation_input2->setPlaceholderText("(Optional) Enter alternative installation path");
            ui->uname_label_2->hide();
            ui->unameInput2->hide();
            ui->pword_label_2->hide();
            ui->pwordInput2->hide();
            ui->alias_label_2->hide();
            ui->aliasInput2->hide();
            ui->launch_label2->hide();
            ui->edit_btn2->hide();
            ui->save_btn2->hide();
            ui->save_btn2_noInc->hide();
            ui->remove_bt2->hide();
            ui->launch_btn2->hide();
            ui->status_label_2->hide();
            hide_file_location(2);

            ui->addClient_btn2->show();
            ui->addClient_label2->show();
            break;
        }
        case 3:
        {
            ui->unameInput3->setPlaceholderText("Enter your Toontown Username...");
            ui->pwordInput3->setPlaceholderText("Enter your Toontown Password...");
            ui->aliasInput3->setPlaceholderText("Enter an alias (optional)");
            ui->fileLocation_input3->setPlaceholderText("(Optional) Enter alternative installation path");
            ui->uname_label_3->hide();
            ui->unameInput3->hide();
            ui->pword_label_3->hide();
            ui->pwordInput3->hide();
            ui->alias_label_3->hide();
            ui->aliasInput3->hide();
            ui->launch_label3->hide();
            ui->edit_btn3->hide();
            ui->save_btn3->hide();
            ui->save_btn3_noInc->hide();
            ui->remove_bt3->hide();
            ui->launch_btn3->hide();
            ui->status_label_3->hide();
            hide_file_location(3);

            ui->addClient_btn3->show();
            ui->addClient_label3->show();
            break;
        }
        default:
            QMessageBox::critical(this, "Internal Error", QString("Unknown index %1 in state_freshLoad").arg(which_one));
            return;
    }
}

void MainWindow::state_registeredLoad(uint8_t how_many)
{
    ui->fileLocation_input1->setPlaceholderText("(Optional) Enter alternative installation path");
    ui->uname_label_1->hide();
    ui->unameInput1->hide();
    ui->pword_label_1->hide();
    ui->pwordInput1->hide();
    ui->alias_label_1->hide();
    ui->aliasInput1->hide();
    ui->save_btn1->hide();
    ui->save_btn1_noInc->hide();
    ui->addClient_btn1->hide();
    ui->addClient_label1->hide();
    ui->status_label_1->hide();

    ui->fileLocation_input2->setPlaceholderText("(Optional) Enter alternative installation path");
    ui->uname_label_2->hide();
    ui->unameInput2->hide();
    ui->pword_label_2->hide();
    ui->pwordInput2->hide();
    ui->alias_label_2->hide();
    ui->aliasInput2->hide();
    ui->save_btn2->hide();
    ui->save_btn2_noInc->hide();
    ui->addClient_btn2->hide();
    ui->addClient_label2->hide();
    ui->status_label_2->hide();

    ui->fileLocation_input3->setPlaceholderText("(Optional) Enter alternative installation path");
    ui->uname_label_3->hide();
    ui->unameInput3->hide();
    ui->pword_label_3->hide();
    ui->pwordInput3->hide();
    ui->alias_label_3->hide();
    ui->aliasInput3->hide();
    ui->save_btn3->hide();
    ui->save_btn3_noInc->hide();
    ui->addClient_btn3->hide();
    ui->addClient_label3->hide();
    ui->status_label_3->hide();


    std::cout << "decrypting with m_numCreds = " << static_cast<int>(m_numCreds) << '\n';
    std::vector<enc::ToontownLogins> tmp_login_struct = enc::fetch_toontownCreds(m_toontownLoginsPath.keyPath, m_toontownLoginsPath.credPath, m_numCreds);

    switch(how_many)
    {
        case 1:
        {
            if(tmp_login_struct[0].alias.empty())
            {
                ui->aliasInput1->setPlaceholderText("Enter an alias (optional)");
                ui->launch_label1->setText(QString::fromStdString("Launch " + tmp_login_struct[0].username));
            }
            else
                ui->launch_label1->setText(QString::fromStdString("Launch " + tmp_login_struct[0].alias));

            //remove if problems, added here
            ui->fileLocation_input1->setText(QString::fromStdString(tmp_login_struct[0].launcherPath));
            ui->launch_btn1->show();
            display_file_location(1);

            state_freshLoad(2);
            state_freshLoad(3);
            break;
        }
        case 2:
        {
            if(tmp_login_struct[0].alias.empty())
            {
                ui->aliasInput1->setPlaceholderText("Enter an alias (optional)");
                ui->launch_label1->setText(QString::fromStdString("Launch " + tmp_login_struct[0].username));
            }
            else
                ui->launch_label1->setText(QString::fromStdString("Launch " + tmp_login_struct[0].alias));
            
            if(tmp_login_struct[1].alias.empty())
            {
                ui->aliasInput2->setPlaceholderText("Enter an alias (optional)");
                ui->launch_label2->setText(QString::fromStdString("Launch " + tmp_login_struct[1].username));
            }
            else
                ui->launch_label2->setText(QString::fromStdString("Launch " + tmp_login_struct[1].alias));
                        
            ui->fileLocation_input1->setText(QString::fromStdString(tmp_login_struct[0].launcherPath));
            ui->fileLocation_input2->setText(QString::fromStdString(tmp_login_struct[1].launcherPath));
            ui->launch_btn1->show();
            display_file_location(1);
            ui->launch_btn2->show();
            display_file_location(2);
            state_freshLoad(3);

            break;
        }
        case 3:
        {
            if(tmp_login_struct[0].alias.empty())
            {
                ui->aliasInput1->setPlaceholderText("Enter an alias (optional)");
                ui->launch_label1->setText(QString::fromStdString("Launch " + tmp_login_struct[0].username));
            }
            else
                ui->launch_label1->setText(QString::fromStdString("Launch " + tmp_login_struct[0].alias));
            
            if(tmp_login_struct[1].alias.empty())
            {
                ui->aliasInput2->setPlaceholderText("Enter an alias (optional)");
                ui->launch_label2->setText(QString::fromStdString("Launch " + tmp_login_struct[1].username));
            }
            else
                ui->launch_label2->setText(QString::fromStdString("Launch " + tmp_login_struct[1].alias));
            
            if(tmp_login_struct[2].alias.empty())
            {
                ui->aliasInput3->setPlaceholderText("Enter an alias (optional)");
                ui->launch_label3->setText(QString::fromStdString("Launch " + tmp_login_struct[2].username));
            }
            else
                ui->launch_label3->setText(QString::fromStdString("Launch " + tmp_login_struct[2].alias));

            ui->fileLocation_input1->setText(QString::fromStdString(tmp_login_struct[0].launcherPath));
            ui->fileLocation_input2->setText(QString::fromStdString(tmp_login_struct[1].launcherPath));
            ui->fileLocation_input3->setText(QString::fromStdString(tmp_login_struct[2].launcherPath));
            ui->launch_btn1->show();
            display_file_location(1);
            ui->launch_btn2->show();
            display_file_location(2);
            ui->launch_btn3->show();
            display_file_location(3);

            break;
        }
        default:
            QMessageBox::critical(this, "Internal Error", QString("Unknown index %1 in state_registeredLoad").arg(how_many));
            return;
    }
}

void MainWindow::state_addClientPressed(uint8_t which_button)
{
    switch(which_button)
    {
        case 1:
        {
            //hide add client
            ui->addClient_btn1->hide();
            ui->addClient_label1->hide();
            
            //show enter credentials
            ui->uname_label_1->show();
            ui->unameInput1->show();
            ui->pword_label_1->show();
            ui->pwordInput1->show();
            ui->alias_label_1->show();
            ui->aliasInput1->show();
            ui->save_btn1->show();
            break;
        }
        case 2:
        {
            //hide add client
            ui->addClient_btn2->hide();
            ui->addClient_label2->hide();
            
            //show enter credentials
            ui->uname_label_2->show();
            ui->unameInput2->show();
            ui->pword_label_2->show();
            ui->pwordInput2->show();
            ui->alias_label_2->show();
            ui->aliasInput2->show();
            ui->save_btn2->show();
            break;
        }
        case 3:
        {
            //hide add client
            ui->addClient_btn3->hide();
            ui->addClient_label3->hide();
            
            //show enter credentials
            ui->uname_label_3->show();
            ui->unameInput3->show();
            ui->pword_label_3->show();
            ui->pwordInput3->show();
            ui->alias_label_3->show();
            ui->aliasInput3->show();
            ui->save_btn3->show();
            break;
        }
        default:
            QMessageBox::critical(this, "Internal Error", QString("Unknown index %1 in state_addClientPressed").arg(which_button));
            return;
    }
}

void MainWindow::state_saveButtonPressed(uint8_t which_button)
{
    switch(which_button)
    {
        case 1 : 
        {
            //hide enter credentials
            ui->uname_label_1->hide();
            ui->unameInput1->hide();
            ui->pword_label_1->hide();
            ui->pwordInput1->hide();
            ui->alias_label_1->hide();
            ui->aliasInput1->hide();
            ui->save_btn1->hide();

            //save elements
            std::string username_1 = ui->unameInput1->text().toStdString();
            std::string pname_1 = ui->pwordInput1->text().toStdString();
            std::string alias_1 = ui->aliasInput1->text().toStdString();

            //didnt enter username or password
            bool noPass = false;
            if(username_1.empty())
            {
                ui->unameInput1->setPlaceholderText("Must enter a username!");
                QPalette usr = ui->unameInput1->palette();
                usr.setColor(QPalette::PlaceholderText, Qt::red);
                ui->unameInput1->setPalette(usr);
                noPass = true;
            }
            if(pname_1.empty())
            {
                ui->pwordInput1->setPlaceholderText("Must enter a password!");
                QPalette p = ui->pwordInput1->palette();
                p.setColor(QPalette::PlaceholderText, Qt::red);
                ui->pwordInput1->setPalette(p);
                noPass = true;
            }
            if(noPass)
            {
                ui->uname_label_1->show();
                ui->unameInput1->show();
                ui->pword_label_1->show();
                ui->pwordInput1->show();
                ui->alias_label_1->show();
                ui->aliasInput1->show();
                ui->save_btn1->show();
                ui->launch_btn1->show();
                return;
            }

            // Fetch all stored entries, replace slot 0 in-place, re-encrypt.
            // encrypt_to_file_append would append a duplicate instead of updating.
            std::vector<enc::ToontownLogins> all_1 = enc::fetch_toontownCreds(
                m_toontownLoginsPath.keyPath, m_toontownLoginsPath.credPath, m_numCreds);
            all_1[0].username    = username_1;
            all_1[0].password    = pname_1;
            all_1[0].alias       = alias_1;
            all_1[0].launcherPath = ui->fileLocation_input1->text().toStdString();
            std::string blob_1;
            for(const auto& e : all_1)
                blob_1 += e.username + '\n' + e.password + '\n' + e.alias + '\n' + e.launcherPath + '\n';
            unsigned char key[crypto_secretbox_KEYBYTES];
            enc::load_keyfile(m_toontownLoginsPath.keyPath, key);
            enc::encrypt_to_file(blob_1, m_toontownLoginsPath.credPath, key);
            enc::store_numCreds(++m_numCreds);

            //show alias
            if(!alias_1.empty())
                ui->launch_label1->setText(QString::fromStdString("Launch: " + alias_1));
            else
                ui->launch_label1->setText(QString::fromStdString("Launch: " + username_1));

            ui->unameInput1->setStyleSheet("color: black;");
            ui->pwordInput1->setStyleSheet("color: black;");
            //show launch/edit/remove
            ui->launch_label1->show();
            ui->edit_btn1->show();
            ui->remove_bt1->show();
            ui->launch_btn1->show();
            display_file_location(1);
            break;
        }
        case 2:
        {
            //hide enter credentials
            ui->uname_label_2->hide();
            ui->unameInput2->hide();
            ui->pword_label_2->hide();
            ui->pwordInput2->hide();
            ui->alias_label_2->hide();
            ui->aliasInput2->hide();
            ui->save_btn2->hide();

            //save elements
            std::string username_2 = ui->unameInput2->text().toStdString();
            std::string pname_2 = ui->pwordInput2->text().toStdString();
            std::string alias_2 = ui->aliasInput2->text().toStdString();

            //didnt enter username or password
            bool noPass = false;
            if(username_2.empty())
            {
                ui->unameInput2->setPlaceholderText("Must enter a username!");
                QPalette usr = ui->unameInput2->palette();
                usr.setColor(QPalette::PlaceholderText, Qt::red);
                ui->unameInput2->setPalette(usr);
                noPass = true;
            }
            if(pname_2.empty())
            {
                ui->pwordInput2->setPlaceholderText("Must enter a password!");
                QPalette p = ui->pwordInput2->palette();
                p.setColor(QPalette::PlaceholderText, Qt::red);
                ui->pwordInput2->setPalette(p);
                noPass = true;
            }
            if(noPass)
            {
                ui->uname_label_2->show();
                ui->unameInput2->show();
                ui->pword_label_2->show();
                ui->pwordInput2->show();
                ui->alias_label_2->show();
                ui->aliasInput2->show();
                ui->save_btn2->show();
                ui->launch_btn2->show();
                return;
            }

            // Fetch all stored entries, replace slot 1 in-place, re-encrypt.
            std::vector<enc::ToontownLogins> all_2 = enc::fetch_toontownCreds(
                m_toontownLoginsPath.keyPath, m_toontownLoginsPath.credPath, m_numCreds);
            all_2[1].username    = username_2;
            all_2[1].password    = pname_2;
            all_2[1].alias       = alias_2;
            all_2[1].launcherPath = ui->fileLocation_input2->text().toStdString();
            std::string blob_2;
            for(const auto& e : all_2)
                blob_2 += e.username + '\n' + e.password + '\n' + e.alias + '\n' + e.launcherPath + '\n';
            unsigned char key[crypto_secretbox_KEYBYTES];
            enc::load_keyfile(m_toontownLoginsPath.keyPath, key);
            enc::encrypt_to_file(blob_2, m_toontownLoginsPath.credPath, key);
            enc::store_numCreds(++m_numCreds);

            //show alias
            if(!alias_2.empty())
                ui->launch_label2->setText(QString::fromStdString("Launch: " + alias_2));
            else
                ui->launch_label2->setText(QString::fromStdString("Launch: " + username_2));

            ui->unameInput2->setStyleSheet("color: black;");
            ui->pwordInput2->setStyleSheet("color: black;");
            //show launch/edit/remove
            ui->launch_label2->show();
            ui->edit_btn2->show();
            ui->remove_bt2->show();
            ui->launch_btn2->show();
            display_file_location(2);
            break;
        }

        case 3:
        {
            //hide enter credentials
            ui->uname_label_3->hide();
            ui->unameInput3->hide();
            ui->pword_label_3->hide();
            ui->pwordInput3->hide();
            ui->alias_label_3->hide();
            ui->aliasInput3->hide();
            ui->save_btn3->hide();

            //save elements
            std::string username_3 = ui->unameInput3->text().toStdString();
            std::string pname_3 = ui->pwordInput3->text().toStdString();
            std::string alias_3 = ui->aliasInput3->text().toStdString();

            //didnt enter username or password
            bool noPass = false;
            if(username_3.empty())
            {
                ui->unameInput3->setPlaceholderText("Must enter a username!");
                QPalette usr = ui->unameInput3->palette();
                usr.setColor(QPalette::PlaceholderText, Qt::red);
                ui->unameInput3->setPalette(usr);
                noPass = true;
            }
            if(pname_3.empty())
            {
                ui->pwordInput3->setPlaceholderText("Must enter a password!");
                QPalette p = ui->pwordInput3->palette();
                p.setColor(QPalette::PlaceholderText, Qt::red);
                ui->pwordInput3->setPalette(p);
                noPass = true;
            }
            if(noPass)
            {
                ui->uname_label_3->show();
                ui->unameInput3->show();
                ui->pword_label_3->show();
                ui->pwordInput3->show();
                ui->alias_label_3->show();
                ui->aliasInput3->show();
                ui->save_btn3->show();
                ui->launch_btn3->show();
                return;
            }

            // Fetch all stored entries, replace slot 2 in-place, re-encrypt.
            std::vector<enc::ToontownLogins> all_3 = enc::fetch_toontownCreds(
                m_toontownLoginsPath.keyPath, m_toontownLoginsPath.credPath, m_numCreds);
            all_3[2].username    = username_3;
            all_3[2].password    = pname_3;
            all_3[2].alias       = alias_3;
            all_3[2].launcherPath = ui->fileLocation_input3->text().toStdString();
            std::string blob_3;
            for(const auto& e : all_3)
                blob_3 += e.username + '\n' + e.password + '\n' + e.alias + '\n' + e.launcherPath + '\n';
            unsigned char key[crypto_secretbox_KEYBYTES];
            enc::load_keyfile(m_toontownLoginsPath.keyPath, key);
            enc::encrypt_to_file(blob_3, m_toontownLoginsPath.credPath, key);
            enc::store_numCreds(++m_numCreds);

            //show alias
            if(!alias_3.empty())
                ui->launch_label3->setText(QString::fromStdString("Launch: " + alias_3));
            else
                ui->launch_label3->setText(QString::fromStdString("Launch: " + username_3));

            ui->unameInput3->setStyleSheet("color: black;");
            ui->pwordInput3->setStyleSheet("color: black;");

            //show launch/edit/remove
            ui->launch_label3->show();
            ui->edit_btn3->show();
            ui->remove_bt3->show();
            ui->launch_btn3->show();
            display_file_location(3);
            break;
        }
        default:
            QMessageBox::critical(this, "Internal Error", QString("Unknown index %1 in state_saveButtonPressed").arg(which_button));
            return;
    }
}

void MainWindow::state_removeButtonPressed(uint8_t which_button)
{
    if(which_button < 1 || which_button > 3)
    {
        QMessageBox::critical(this, "Internal Error", QString("Unknown index %1 in state_removeButtonPressed").arg(which_button));
        return;
    }

    unsigned char key[crypto_secretbox_KEYBYTES];
    enc::load_keyfile(m_toontownLoginsPath.keyPath, key);
    enc::remove_from_file(m_toontownLoginsPath.keyPath, m_toontownLoginsPath.credPath, m_numCreds, which_button, key);
    enc::store_numCreds(--m_numCreds);

    refreshClientSlots();
}

void MainWindow::state_editButtonPressed(uint8_t which_button)
{
    switch(which_button)
    {
        case 1:
        {
            ui->edit_btn1->hide();
            ui->remove_bt1->hide();
            ui->launch_label1->hide();
            ui->launch_btn1->hide();
            ui->status_label_1->hide();
            hide_file_location(1);

            ui->uname_label_1->show();
            ui->unameInput1->show();
            ui->pword_label_1->show();
            ui->pwordInput1->show();
            ui->alias_label_1->show();
            ui->aliasInput1->show();
            ui->save_btn1_noInc->show();
            break;
        }
        case 2:
        {
            ui->edit_btn2->hide();
            ui->remove_bt2->hide();
            ui->launch_label2->hide();
            ui->launch_btn2->hide();
            ui->status_label_2->hide();
            hide_file_location(2);

            ui->uname_label_2->show();
            ui->unameInput2->show();
            ui->pword_label_2->show();
            ui->pwordInput2->show();
            ui->alias_label_2->show();
            ui->aliasInput2->show();
            ui->save_btn2_noInc->show();
            break;
        }
        case 3:
        {
            ui->edit_btn3->hide();
            ui->remove_bt3->hide();
            ui->launch_label3->hide();
            ui->launch_btn3->hide();
            ui->status_label_3->hide();
            hide_file_location(3);

            ui->uname_label_3->show();
            ui->unameInput3->show();
            ui->pword_label_3->show();
            ui->pwordInput3->show();
            ui->alias_label_3->show();
            ui->aliasInput3->show();
            ui->save_btn3_noInc->show();
            break;
        }
        default:
            QMessageBox::critical(this, "Internal Error", QString("Unknown index %1 in state_editButtonPressed").arg(which_button));
            return;
    }
}

void MainWindow::state_saveNoIncButtonPressed(uint8_t which_button)
{
    switch(which_button)
    {
        case 1 : 
        {
            //hide enter credentials
            ui->uname_label_1->hide();
            ui->unameInput1->hide();
            ui->pword_label_1->hide();
            ui->pwordInput1->hide();
            ui->alias_label_1->hide();
            ui->aliasInput1->hide();
            ui->save_btn1_noInc->hide();

            //save elements
            std::string username_1 = ui->unameInput1->text().toStdString();
            std::string pname_1 = ui->pwordInput1->text().toStdString();
            std::string alias_1 = ui->aliasInput1->text().toStdString();

            //didnt enter username or password
            bool noPass = false;
            if(username_1.empty())
            {
                ui->unameInput1->setPlaceholderText("Must enter a username!");
                QPalette usr = ui->unameInput1->palette();
                usr.setColor(QPalette::PlaceholderText, Qt::red);
                ui->unameInput1->setPalette(usr);
                noPass = true;
            }
            if(pname_1.empty())
            {
                ui->pwordInput1->setPlaceholderText("Must enter a password!");
                QPalette p = ui->pwordInput1->palette();
                p.setColor(QPalette::PlaceholderText, Qt::red);
                ui->pwordInput1->setPalette(p);
                noPass = true;
            }
            if(noPass)
            {
                ui->uname_label_1->show();
                ui->unameInput1->show();
                ui->pword_label_1->show();
                ui->pwordInput1->show();
                ui->alias_label_1->show();
                ui->aliasInput1->show();
                ui->save_btn1_noInc->show();
                return;
            }

            // Fetch all stored entries, replace slot 0 in-place, re-encrypt.
            // encrypt_to_file_append would append a duplicate instead of updating.
            std::vector<enc::ToontownLogins> all_1 = enc::fetch_toontownCreds(
                m_toontownLoginsPath.keyPath, m_toontownLoginsPath.credPath, m_numCreds);
            all_1[0].username    = username_1;
            all_1[0].password    = pname_1;
            all_1[0].alias       = alias_1;
            all_1[0].launcherPath = ui->fileLocation_input1->text().toStdString();
            std::string blob_1;
            for(const auto& e : all_1)
                blob_1 += e.username + '\n' + e.password + '\n' + e.alias + '\n' + e.launcherPath + '\n';
            unsigned char key[crypto_secretbox_KEYBYTES];
            enc::load_keyfile(m_toontownLoginsPath.keyPath, key);
            enc::encrypt_to_file(blob_1, m_toontownLoginsPath.credPath, key);

            //update label
            if(!alias_1.empty())
                ui->launch_label1->setText(QString::fromStdString("Launch: " + alias_1));
            else
                ui->launch_label1->setText(QString::fromStdString("Launch: " + username_1));

            //show launch/edit/remove
            ui->launch_label1->show();
            ui->edit_btn1->show();
            ui->remove_bt1->show();
            ui->launch_btn1->show();
            display_file_location(1);
            break;
        }
        case 2:
        {
            //hide enter credentials
            ui->uname_label_2->hide();
            ui->unameInput2->hide();
            ui->pword_label_2->hide();
            ui->pwordInput2->hide();
            ui->alias_label_2->hide();
            ui->aliasInput2->hide();
            ui->save_btn2_noInc->hide();

            //save elements
            std::string username_2 = ui->unameInput2->text().toStdString();
            std::string pname_2 = ui->pwordInput2->text().toStdString();
            std::string alias_2 = ui->aliasInput2->text().toStdString();

            //didnt enter username or password
            bool noPass = false;
            if(username_2.empty())
            {
                ui->unameInput2->setPlaceholderText("Must enter a username!");
                QPalette usr = ui->unameInput2->palette();
                usr.setColor(QPalette::PlaceholderText, Qt::red);
                ui->unameInput2->setPalette(usr);
                noPass = true;
            }
            if(pname_2.empty())
            {
                ui->pwordInput2->setPlaceholderText("Must enter a password!");
                QPalette p = ui->pwordInput2->palette();
                p.setColor(QPalette::PlaceholderText, Qt::red);
                ui->pwordInput2->setPalette(p);
                noPass = true;
            }
            if(noPass)
            {
                ui->uname_label_2->show();
                ui->unameInput2->show();
                ui->pword_label_2->show();
                ui->pwordInput2->show();
                ui->alias_label_2->show();
                ui->aliasInput2->show();
                ui->save_btn2_noInc->show();
                return;
            }

            // Fetch all stored entries, replace slot 1 in-place, re-encrypt.
            std::vector<enc::ToontownLogins> all_2 = enc::fetch_toontownCreds(
                m_toontownLoginsPath.keyPath, m_toontownLoginsPath.credPath, m_numCreds);
            all_2[1].username    = username_2;
            all_2[1].password    = pname_2;
            all_2[1].alias       = alias_2;
            all_2[1].launcherPath = ui->fileLocation_input2->text().toStdString();
            std::string blob_2;
            for(const auto& e : all_2)
                blob_2 += e.username + '\n' + e.password + '\n' + e.alias + '\n' + e.launcherPath + '\n';
            unsigned char key[crypto_secretbox_KEYBYTES];
            enc::load_keyfile(m_toontownLoginsPath.keyPath, key);
            enc::encrypt_to_file(blob_2, m_toontownLoginsPath.credPath, key);

            //update label
            if(!alias_2.empty())
                ui->launch_label2->setText(QString::fromStdString("Launch: " + alias_2));
            else
                ui->launch_label2->setText(QString::fromStdString("Launch: " + username_2));

            //show launch/edit/remove
            ui->launch_label2->show();
            ui->edit_btn2->show();
            ui->remove_bt2->show();
            ui->launch_btn2->show();
            display_file_location(2);
            break;
        }

        case 3:
        {
            //hide enter credentials
            ui->uname_label_3->hide();
            ui->unameInput3->hide();
            ui->pword_label_3->hide();
            ui->pwordInput3->hide();
            ui->alias_label_3->hide();
            ui->aliasInput3->hide();
            ui->save_btn3_noInc->hide();

            //save elements
            std::string username_3 = ui->unameInput3->text().toStdString();
            std::string pname_3 = ui->pwordInput3->text().toStdString();
            std::string alias_3 = ui->aliasInput3->text().toStdString();

            //didnt enter username or password
            bool noPass = false;
            if(username_3.empty())
            {
                ui->unameInput3->setPlaceholderText("Must enter a username!");
                QPalette usr = ui->unameInput3->palette();
                usr.setColor(QPalette::PlaceholderText, Qt::red);
                ui->unameInput3->setPalette(usr);
                noPass = true;
            }
            if(pname_3.empty())
            {
                ui->pwordInput3->setPlaceholderText("Must enter a password!");
                QPalette p = ui->pwordInput3->palette();
                p.setColor(QPalette::PlaceholderText, Qt::red);
                ui->pwordInput3->setPalette(p);
                noPass = true;
            }
            if(noPass)
            {
                ui->uname_label_3->show();
                ui->unameInput3->show();
                ui->pword_label_3->show();
                ui->pwordInput3->show();
                ui->alias_label_3->show();
                ui->aliasInput3->show();
                ui->save_btn3_noInc->show();
                return;
            }

            // Fetch all stored entries, replace slot 2 in-place, re-encrypt.
            std::vector<enc::ToontownLogins> all_3 = enc::fetch_toontownCreds(
                m_toontownLoginsPath.keyPath, m_toontownLoginsPath.credPath, m_numCreds);
            all_3[2].username    = username_3;
            all_3[2].password    = pname_3;
            all_3[2].alias       = alias_3;
            all_3[2].launcherPath = ui->fileLocation_input3->text().toStdString();
            std::string blob_3;
            for(const auto& e : all_3)
                blob_3 += e.username + '\n' + e.password + '\n' + e.alias + '\n' + e.launcherPath + '\n';
            unsigned char key[crypto_secretbox_KEYBYTES];
            enc::load_keyfile(m_toontownLoginsPath.keyPath, key);
            enc::encrypt_to_file(blob_3, m_toontownLoginsPath.credPath, key);

            //update label
            if(!alias_3.empty())
                ui->launch_label3->setText(QString::fromStdString("Launch: " + alias_3));
            else
                ui->launch_label3->setText(QString::fromStdString("Launch: " + username_3));

            //show launch/edit/remove
            ui->launch_label3->show();
            ui->edit_btn3->show();
            ui->remove_bt3->show();
            ui->launch_btn3->show();
            display_file_location(3);
            break;
        }
        default:
            QMessageBox::critical(this, "Internal Error", QString("Unknown index %1 in state_saveNoIncButtonPressed").arg(which_button));
            return;
    }
}

void MainWindow::display_file_location(uint8_t which_one)
{
    switch(which_one)
    {
        case 1:
        {
            ui->installLoc_label1->show();
            ui->fileLocation_input1->show();
            ui->manual_loc_btnEDIT1->show();
            break;
        }
        case 2:
        {
            ui->installLoc_label2->show();
            ui->fileLocation_input2->show();
            ui->manual_loc_btnEDIT2->show();
            break;
        }
        case 3:
        {
            ui->installLoc_label3->show();
            ui->fileLocation_input3->show();
            ui->manual_loc_btnEDIT3->show();
            break;
        }
        default:
            QMessageBox::critical(this, "Internal Error", QString("Unknown index %1 in display_file_location").arg(which_one));
            return;
    }
}

void MainWindow::hide_file_location(uint8_t which_one)
{
    switch(which_one)
    {
        case 1:
        {
            ui->installLoc_label1->hide();
            ui->fileLocation_input1->hide();
            ui->manual_loc_btnEDIT1->hide();
            break;
        }
        case 2:
        {
            ui->installLoc_label2->hide();
            ui->fileLocation_input2->hide();
            ui->manual_loc_btnEDIT2->hide();
            break;
        }
        case 3:
        {
            ui->installLoc_label3->hide();
            ui->fileLocation_input3->hide();
            ui->manual_loc_btnEDIT3->hide();
            break;
        }
        default:
            QMessageBox::critical(this, "Internal Error", QString("Unknown index %1 in hide_file_location").arg(which_one));
            return;
    }
}

void MainWindow::setFonts()
{
    ui->unameInput1->setFont(m_ttrFont);
    ui->pwordInput1->setFont(m_ttrFont);
    ui->uname_label_1->setFont(m_ttrFontXL);
    ui->pword_label_1->setFont(m_ttrFontXL);
    ui->alias_label_1->setFont(m_ttrFontXL);
    ui->aliasInput1->setFont(m_ttrFont);
    ui->launch_label1->setFont(m_ttrFontXL);
    ui->edit_btn1->setFont(m_ttrFontLarge);
    ui->save_btn1->setFont(m_ttrFontLarge);
    ui->save_btn1_noInc->setFont(m_ttrFontLarge);
    ui->remove_bt1->setFont(m_ttrFontLarge);
    ui->launch_btn1->setFont(m_ttrFontLarge);
    ui->addClient_label1->setFont(m_ttrFontXL);
    ui->pwordInput1->setEchoMode(QLineEdit::Password);
    ui->status_label_1->setFont(m_ttrFontLarge);
    ui->installLoc_label1->setFont(m_ttrFontXL);
    ui->fileLocation_input1->setFont(m_ttrFontSmall);
    ui->manual_loc_btnEDIT1->setFont(m_ttrFontXL);

    ui->unameInput2->setFont(m_ttrFont);
    ui->pwordInput2->setFont(m_ttrFont);
    ui->uname_label_2->setFont(m_ttrFontXL);
    ui->pword_label_2->setFont(m_ttrFontXL);
    ui->alias_label_2->setFont(m_ttrFontXL);
    ui->aliasInput2->setFont(m_ttrFont);
    ui->launch_label2->setFont(m_ttrFontXL);
    ui->edit_btn2->setFont(m_ttrFontLarge);
    ui->save_btn2->setFont(m_ttrFontLarge);
    ui->save_btn2_noInc->setFont(m_ttrFontLarge);
    ui->remove_bt2->setFont(m_ttrFontLarge);
    ui->launch_btn2->setFont(m_ttrFontLarge);
    ui->addClient_label2->setFont(m_ttrFontXL);
    ui->pwordInput2->setEchoMode(QLineEdit::Password);
    ui->status_label_2->setFont(m_ttrFontLarge);
    ui->installLoc_label2->setFont(m_ttrFontXL);
    ui->fileLocation_input2->setFont(m_ttrFontSmall);
    ui->manual_loc_btnEDIT2->setFont(m_ttrFontXL);

    ui->unameInput3->setFont(m_ttrFont);
    ui->pwordInput3->setFont(m_ttrFont);
    ui->uname_label_3->setFont(m_ttrFontXL);
    ui->pword_label_3->setFont(m_ttrFontXL);
    ui->alias_label_3->setFont(m_ttrFontXL);
    ui->aliasInput3->setFont(m_ttrFont);
    ui->launch_label3->setFont(m_ttrFontXL);
    ui->edit_btn3->setFont(m_ttrFontLarge);
    ui->save_btn3->setFont(m_ttrFontLarge);
    ui->save_btn3_noInc->setFont(m_ttrFontLarge);
    ui->remove_bt3->setFont(m_ttrFontLarge);
    ui->launch_btn3->setFont(m_ttrFontLarge);
    ui->addClient_label3->setFont(m_ttrFontXL);
    ui->pwordInput3->setEchoMode(QLineEdit::Password);
    ui->status_label_3->setFont(m_ttrFontLarge);
    ui->installLoc_label3->setFont(m_ttrFontXL);
    ui->fileLocation_input3->setFont(m_ttrFontSmall);
    ui->manual_loc_btnEDIT3->setFont(m_ttrFontXL);

    //doodle training page
    ui->start_trick1Btn->setFont(m_ttrFontLarge);
    ui->start_trick2Btn->setFont(m_ttrFontLarge);
    ui->start_trick3Btn->setFont(m_ttrFontLarge);
    ui->start_trick4Btn->setFont(m_ttrFontLarge);
    ui->start_trick5Btn->setFont(m_ttrFontLarge);
    ui->start_trick6Btn->setFont(m_ttrFontLarge);
    ui->start_trick7Btn->setFont(m_ttrFontLarge);
    ui->stop_trainingBtn->setFont(m_ttrFontLarge);
    ui->current_trickLabel->setFont(m_ttrFontLarge);
    ui->labelBox->setFont(m_ttrFont);
    ui->labelBox_2->setFont(m_ttrFont);
    ui->labelBox_3->setFont(m_ttrFont);
    ui->labelBox_4->setFont(m_ttrFont);
    ui->labelBox_5->setFont(m_ttrFont);
    ui->labelBox_6->setFont(m_ttrFont);
    ui->labelBox_7->setFont(m_ttrFont);
    ui->resolutionLabel->setFont(m_ttrFontLarge);

    //dual toon page
    ui->start_arrowKeysBtn->setFont(m_ttrFontLarge);
    ui->start_WASDBtn->setFont(m_ttrFontLarge);
    ui->stop_dualBtn->setFont(m_ttrFontLarge);
    ui->dual_headerLabel->setFont(m_ttrFontLarge);
    ui->whichRunningLabel->setFont(m_ttrFontLarge);
    ui->typingLabel->setFont(m_ttrFontLarge);

    //invasions
    ui->invasionCounterLabel->setFont(m_ttrFontLarge);
}

void MainWindow::setNoFocusItems()
{
    ui->xBtn->setFocusPolicy(Qt::NoFocus);
    ui->minBtn->setFocusPolicy(Qt::NoFocus);
    ui->homeBtn->setFocusPolicy(Qt::NoFocus);
    ui->stop_dualBtn->setFocusPolicy(Qt::NoFocus);
    ui->start_arrowKeysBtn->setFocusPolicy(Qt::NoFocus);
    ui->start_WASDBtn->setFocusPolicy(Qt::NoFocus);
    ui->stop_trainingBtn->setFocusPolicy(Qt::NoFocus);

}

void MainWindow::state_launchButton(uint8_t which_button)
{
    try
    {
        switch(which_button)
        {
            case 1:
            {
                std::vector<enc::ToontownLogins> tmp_login_vec = enc::fetch_toontownCreds(m_toontownLoginsPath.keyPath, 
                        m_toontownLoginsPath.credPath, m_numCreds);

                ttr::ToontownLoginInformation result = ttr::toonLauncher_retrieveResponse(tmp_login_vec[0].username, tmp_login_vec[0].password);

                if(!result.error_info.errorMsg.empty())
                {
                    ui->status_label_1->setText(QString::fromStdString(result.error_info.errorMsg));
                    ui->status_label_1->show();
                    return;
                }

                std::string engine_loc;

                if(ui->fileLocation_input1->text().isEmpty())
                {
                    std::optional<std::filesystem::path> enginePath = fd::findTTREngineAuto();
                    if(!enginePath)
                    {
                        ui->status_label_1->setText("Couldn't auto detect install - enter manually");
                        ui->status_label_1->show();
                        return;
                    }   
                    engine_loc = enginePath->string();
                    ui->fileLocation_input1->setText(QString::fromStdString(engine_loc));

                    //persist new found path into this record, in place
                    unsigned char key[crypto_secretbox_KEYBYTES];
                    enc::load_keyfile(m_toontownLoginsPath.keyPath, key);
                    enc::update_installPath(m_toontownLoginsPath.keyPath, m_toontownLoginsPath.credPath, m_numCreds, 1, key, engine_loc);
                }
                else
                {
                    engine_loc = ui->fileLocation_input1->text().toStdString();
                    // persist whatever the user typed, even if invalid, user can fix it later
                    unsigned char key[crypto_secretbox_KEYBYTES];
                    enc::load_keyfile(m_toontownLoginsPath.keyPath, key);
                    enc::update_installPath(m_toontownLoginsPath.keyPath, m_toontownLoginsPath.credPath,m_numCreds, 1, key, engine_loc);
                }

                if(!fd::looksLikeTTREngine(engine_loc))
                {
                    ui->status_label_1->setText("Saved install path looks invalid");
                    ui->status_label_1->show();
                    return;
                }
                if(!ttr::launch_toontown(engine_loc, result.gameServer, result.playCookie))
                {
                    ui->status_label_1->setText("Failed to boot Toontown with provided info");
                    ui->status_label_1->show();
                }

                break;
            }
            case 2:
            {
                std::vector<enc::ToontownLogins> tmp_login_vec = enc::fetch_toontownCreds(m_toontownLoginsPath.keyPath, 
                        m_toontownLoginsPath.credPath, m_numCreds);

                ttr::ToontownLoginInformation result = ttr::toonLauncher_retrieveResponse(tmp_login_vec[1].username, tmp_login_vec[1].password);

                if(!result.error_info.errorMsg.empty())
                {
                    ui->status_label_2->setText(QString::fromStdString(result.error_info.errorMsg));
                    ui->status_label_2->show();
                    return;
                }

                std::string engine_loc;

                if(ui->fileLocation_input2->text().isEmpty())
                {
                    std::optional<std::filesystem::path> enginePath = fd::findTTREngineAuto();
                    if(!enginePath)
                    {
                        ui->status_label_2->setText("Couldn't auto detect install - enter manually");
                        ui->status_label_2->show();
                        return;
                    }   
                    engine_loc = enginePath->string();
                    ui->fileLocation_input2->setText(QString::fromStdString(engine_loc));

                    //persist new found path into this record, in place
                    unsigned char key[crypto_secretbox_KEYBYTES];
                    enc::load_keyfile(m_toontownLoginsPath.keyPath, key);
                    enc::update_installPath(m_toontownLoginsPath.keyPath, m_toontownLoginsPath.credPath, m_numCreds, 2, key, engine_loc);
                }
                else
                {
                    engine_loc = ui->fileLocation_input2->text().toStdString();
                    // persist whatever the user typed, even if invalid, user can fix it later
                    unsigned char key[crypto_secretbox_KEYBYTES];
                    enc::load_keyfile(m_toontownLoginsPath.keyPath, key);
                    enc::update_installPath(m_toontownLoginsPath.keyPath, m_toontownLoginsPath.credPath,m_numCreds, 1, key, engine_loc);
                }

                if(!fd::looksLikeTTREngine(engine_loc))
                {
                    ui->status_label_2->setText("Saved install path looks invalid");
                    ui->status_label_2->show();
                    return;
                }
                if(!ttr::launch_toontown(engine_loc, result.gameServer, result.playCookie))
                {
                    ui->status_label_2->setText("Failed to boot Toontown with provided info");
                    ui->status_label_2->show();
                }

                break;
            }
            case 3:
            {
                std::vector<enc::ToontownLogins> tmp_login_vec = enc::fetch_toontownCreds(m_toontownLoginsPath.keyPath, 
                        m_toontownLoginsPath.credPath, m_numCreds);

                ttr::ToontownLoginInformation result = ttr::toonLauncher_retrieveResponse(tmp_login_vec[2].username, tmp_login_vec[2].password);

                if(!result.error_info.errorMsg.empty())
                {
                    ui->status_label_3->setText(QString::fromStdString(result.error_info.errorMsg));
                    ui->status_label_3->show();
                    return;
                }

                std::string engine_loc;

                if(ui->fileLocation_input3->text().isEmpty())
                {
                    std::optional<std::filesystem::path> enginePath = fd::findTTREngineAuto();
                    if(!enginePath)
                    {
                        ui->status_label_3->setText("Couldn't auto detect install - enter manually");
                        ui->status_label_3->show();
                        return;
                    }   
                    engine_loc = enginePath->string();
                    ui->fileLocation_input3->setText(QString::fromStdString(engine_loc));

                    //persist new found path into this record, in place
                    unsigned char key[crypto_secretbox_KEYBYTES];
                    enc::load_keyfile(m_toontownLoginsPath.keyPath, key);
                    enc::update_installPath(m_toontownLoginsPath.keyPath, m_toontownLoginsPath.credPath, m_numCreds, 3, key, engine_loc);
                }
                else
                {
                    engine_loc = ui->fileLocation_input3->text().toStdString();
                    // persist whatever the user typed, even if invalid, user can fix it later
                    unsigned char key[crypto_secretbox_KEYBYTES];
                    enc::load_keyfile(m_toontownLoginsPath.keyPath, key);
                    enc::update_installPath(m_toontownLoginsPath.keyPath, m_toontownLoginsPath.credPath,m_numCreds, 1, key, engine_loc);
                }

                if(!fd::looksLikeTTREngine(engine_loc))
                {
                    ui->status_label_3->setText("Saved install path looks invalid");
                    ui->status_label_3->show();
                    return;
                }
                if(!ttr::launch_toontown(engine_loc, result.gameServer, result.playCookie))
                {
                    ui->status_label_3->setText("Failed to boot Toontown with provided info");
                    ui->status_label_3->show();
                }

                break;
            }
            default:
                //should never happen
            QMessageBox::critical(this, "Internal Error", 
                    QString("Unknown button index %1 in state_launchButton").arg(which_button));
            return;
        }
    }
    catch(const std::exception& e)
    {
        QMessageBox::critical(this, "Launch Error", QString("An error occurred while launching:\n\n") + e.what());
    }
}

void MainWindow::refreshClientSlots()
{
    if(m_numCreds == 0)
    {
        state_freshLoad(1);
        state_freshLoad(2);
        state_freshLoad(3);
    }
    else
        state_registeredLoad(m_numCreds);
}

void MainWindow::doodleTrain(std::vector<ClickStep> where_to_click)
{
    if(m_doodleTrainingActive) return;
    m_doodleTrainingActive = true;

    m_doodleTargetWindow = dir_inp::get_window_via_click();
    m_doodleTrainThread = std::thread([this, where_to_click]()
    {
        while(m_doodleTrainingActive)
            {
                for(size_t i = 0; i < where_to_click.size() && m_doodleTrainingActive; i++)
                {
                    dir_inp::send_mouse_click(m_doodleTargetWindow, where_to_click[i].x, where_to_click[i].y, dir_inp::MOUSE_LEFT, true);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    dir_inp::send_mouse_click(m_doodleTargetWindow, where_to_click[i].x, where_to_click[i].y, dir_inp::MOUSE_LEFT, false);

                    // sleep in small chunks so stop button is responsive
                    int remaining = where_to_click[i].delay_ms;
                    while(remaining > 0 && m_doodleTrainingActive)
                    {
                        int chunk = std::min(remaining, 100);
                        std::this_thread::sleep_for(std::chrono::milliseconds(chunk));
                        remaining -= chunk;
                    }
                }
            }
    });
}

void MainWindow::setLabelBoxes()
{
    m_trickLabels = enc::read_plaintext("config/Doodle/labels.txt");
    ui->labelBox->setCurrentIndex(std::stoi(m_trickLabels[0]));
    ui->labelBox_2->setCurrentIndex(std::stoi(m_trickLabels[1]));
    ui->labelBox_3->setCurrentIndex(std::stoi(m_trickLabels[2]));
    ui->labelBox_4->setCurrentIndex(std::stoi(m_trickLabels[3]));
    ui->labelBox_5->setCurrentIndex(std::stoi(m_trickLabels[4]));
    ui->labelBox_6->setCurrentIndex(std::stoi(m_trickLabels[5]));
    ui->labelBox_7->setCurrentIndex(std::stoi(m_trickLabels[6]));
}

void MainWindow::storeLabelBoxes()
{
    m_trickLabels[0] = std::to_string(ui->labelBox->currentIndex());
    m_trickLabels[1] = std::to_string(ui->labelBox_2->currentIndex());
    m_trickLabels[2] = std::to_string(ui->labelBox_3->currentIndex());
    m_trickLabels[3] = std::to_string(ui->labelBox_4->currentIndex());
    m_trickLabels[4] = std::to_string(ui->labelBox_5->currentIndex());
    m_trickLabels[5] = std::to_string(ui->labelBox_6->currentIndex());
    m_trickLabels[6] = std::to_string(ui->labelBox_7->currentIndex());

    enc::write_plaintext("config/Doodle/labels.txt", m_trickLabels);
}

void MainWindow::set_whichRunningLabel()
{
    if(m_dualToonStatus.both == true)
        ui->whichRunningLabel->setText("Both Toons are receiving input");
    else if(m_dualToonStatus.wasd == true)
        ui->whichRunningLabel->setText("Only WASD Toon is receiving input");
    else if(m_dualToonStatus.arrow_keys == true)
        ui->whichRunningLabel->setText("Only Arrow Keys Toon is receiving input");
    else
        ui->whichRunningLabel->setText("Neither toon is receiving input");
}

void MainWindow::populateInvasionList()
{
    ui->invasionListWidget->clear();
    m_invasionRemaining.clear();
    ui->invasionListWidget->setIconSize(QSize(60, 60));

    for(const auto& inv : m_invasions)
    {
        int remaining = ttr::estimateSecondsRemaining(inv);
        m_invasionRemaining.push_back(remaining);

        QString text = QString::fromStdString(
            inv.district + " | " + inv.cogType + " | " +
            std::to_string(inv.current) + "/" + std::to_string(inv.total) +
            " | " + ttr::formatTime(remaining));

        auto* item = new QListWidgetItem(text);

        // build icon path from cog type
        QString cogName = QString::fromStdString(inv.cogType).toLower().replace(' ', '_');
        QString iconPath = "config/icons/cog_heads/" + cogName + ".png";
        QPixmap pix(iconPath);
        if(!pix.isNull())
            item->setIcon(QIcon(pix.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation)));

        if(remaining < 600)
            item->setForeground(QColor("#ff4444"));
        else
            item->setForeground(Qt::black);
        ui->invasionListWidget->addItem(item);
    }
    ui->invasionCounterLabel->setText(QString::fromStdString(std::to_string(m_invasions.size())));
}

void MainWindow::updateInvasionTimers()
{
    if(m_invasions.empty()) return;

    for(size_t i = 0; i < m_invasions.size() && i < static_cast<size_t>(ui->invasionListWidget->count()); i++)
    {
        if(m_invasionRemaining[i] > 0)
            m_invasionRemaining[i]--;

        QString text = QString::fromStdString(
            m_invasions[i].district + " | " + m_invasions[i].cogType + " | " +
            std::to_string(m_invasions[i].current) + "/" + std::to_string(m_invasions[i].total) +
            " | " + ttr::formatTime(m_invasionRemaining[i]));

        auto* item = ui->invasionListWidget->item(i);
        item->setText(text);

        if(m_invasionRemaining[i] < 600)
            item->setForeground(QColor("#ff4444"));
        else
            item->setForeground(Qt::black);
    }
}

void MainWindow::pollInvasions()
{
    std::thread([this]()
    {
        auto result = ttr::fetchInvasions();
        std::cout << "pollInvasions got " << result.size() << " invasions\n";
        QMetaObject::invokeMethod(this, [this, result]()
        {
            m_invasions = result;
            std::cout << "m_invasions now has " << m_invasions.size() << " entries\n";
            populateInvasionList();
            ui->invasionCounterLabel->setText(QString::fromStdString(std::to_string(m_invasions.size())));
        }, Qt::QueuedConnection);
    }).detach();
}
