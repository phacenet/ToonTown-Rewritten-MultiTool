#pragma once
#include "ttr_api_reqs.hpp"
#include <QMainWindow>
#include <QMouseEvent>
#include <QLabel>
#include <QWebEngineView>
#include <sio_client.h>
#include <qtimer.h>
#include <thread>

struct LoginFilesPath
{
    const std::string keyPath = "config/ToonHQLogin/key.bin";
    const std::string credPath = "config/ToonHQLogin/credentials.bin";
};

struct WhichRunning{ bool none; bool wasd; bool arrow_keys; bool both;};

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    protected:
        void mousePressEvent(QMouseEvent* event) override;
        void mouseMoveEvent(QMouseEvent* event) override;
        bool eventFilter(QObject* object, QEvent* event) override;

    signals:
        void loginAuthenticated();
        void loginFailed();

    private slots:
        void on_xBtnClicked();
        void attemptLogin();
        void submitPressed(const std::string& uName, const std::string& pWord);

    private:
        Ui::MainWindow* ui;
        QFont m_ttrFontSmall;
        QFont m_ttrFont;
        QFont m_ttrFontLarge;
        QFont m_ttrFontXL;
        QPoint m_dragPosition;
        bool m_dragging = false;
        bool m_minimize = false;
        bool m_inPasswordBox = false;
        LoginFilesPath m_loginsPath;
        LoginFilesPath m_toontownLoginsPath{.keyPath = "config/ToontownLogin/key.bin", .credPath = "config/ToontownLogin/credentials.bin"};
        std::string m_orig_csrftoken;
        ttr::ToonHQLoginResult m_toonTown_loginStruct;
        bool m_dontStoreCreds = false;
        ttr::ToonHQToonInformation m_connectedToon;
        uint8_t m_currentPageIndex;
        sio::client* m_sioClient = nullptr;
        QTimer* m_resubscribeTimer = nullptr;
        bool badToonLoad = false;
        uint8_t m_numCreds;
        std::vector<std::string> m_trickLabels = {"0","0","0","0","0","0","0"};
       
        unsigned long m_targetWASDWindow;
        unsigned long m_targetARROWKEYSWindow;
        unsigned long m_doodleTargetWindow;
        std::atomic<bool> m_doodleTrainingActive{false};
        std::atomic<bool> m_dualToonActiveARROWS{false};
        std::atomic<bool> m_dualToonActiveWASD{false};
        std::atomic<bool> m_wasdPaused{false};
        std::atomic<bool> m_hotkeyActive{true};
        std::thread m_doodleTrainThread;
        std::thread m_dualToonThreadArrows;
        std::thread m_dualToonThreadWASD;
        std::thread m_hotkeyThread;
        struct ClickStep{int x; int y; int delay_ms;};
        std::vector<ClickStep> m_doodleTrainStartSteps
            {
                {59, 17, 500}, //open speedchat, delay 0.5s
                {127, 61, 500}, //open pets, delay 0.5s
                {232, 60, 500}, //open tricks, wait 0.5s
            };
        WhichRunning m_dualToonStatus{.none = true, .wasd = false, .arrow_keys = false, .both = false};  
        QTimer* m_invasionPollTimer = nullptr;
        QTimer* m_invasionTickTimer = nullptr;
        std::vector<ttr::InvasionInformation> m_invasions;
        std::vector<int> m_invasionRemaining;
        QWebEngineView* m_browser = nullptr;

        void populateToonList();
        void updateToonRowWidth();
        void loadSelectedToonImg(const QString& url, QLabel* label, QLabel* labelInfo);
        void startBoarding();
        
        void state_freshLoad(uint8_t which_one);
        void state_registeredLoad(uint8_t how_many);
        void state_addClientPressed(uint8_t which_button);
        void state_saveButtonPressed(uint8_t which_button);
        void state_removeButtonPressed(uint8_t which_button);
        void state_editButtonPressed(uint8_t which_button);
        void state_saveNoIncButtonPressed(uint8_t which_button);
        void display_file_location(uint8_t which_one);
        void hide_file_location(uint8_t which_one);
        void sync_file_location(uint8_t which_one);
        void setFonts();
        void setNoFocusItems();
        void state_launchButton(uint8_t which_button);
        void refreshClientSlots();

        void doodleTrain(std::vector<ClickStep> where_to_click);
        void setLabelBoxes();
        void storeLabelBoxes();

        void set_whichRunningLabel();

        void populateInvasionList();
        void updateInvasionTimers();
        void pollInvasions();


};
