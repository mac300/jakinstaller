
TEMPLATE = aux

#----------------------------------------------------------------------------------------
# zanim zbudujemy projekt musimy umieścić pliki wykonywalne i biblioteki dll w katalogu:
# $$PWD/installer/packages/com.github.jakinstaller/data
# i w zależności od trybu budowania wybrać katalogi dla instalatorów
#----------------------------------------------------------------------------------------
CONFIG(debug, debug|release) {
    INSTALLER_OFFLINE = $$OUT_PWD/../../InstallerDebug/Jak.offline
    INSTALLER_ONLINE = $$OUT_PWD/../../InstallerDebug/Jak.online
    PWD_WIN = $$OUT_PWD/../../JakDebug
} else {
    INSTALLER_OFFLINE = $$OUT_PWD/../../InstallerRelease/Jak.offline
    INSTALLER_ONLINE = $$OUT_PWD/../../InstallerRelease/Jak.online
    PWD_WIN = $$OUT_PWD/../../JakRelease
    PACKAGES_ONLINE = $$OUT_PWD/../../repository
}
DESTDIR_WIN = $$PWD/packages/mac30.jak.installer/data
win32 {
    DESTDIR_WIN ~= s,/,\\,g
    PWD_WIN ~= s,/,\\,g
    copydata.commands = $(COPY_DIR) $$PWD_WIN $$DESTDIR_WIN
} else {
    copydata.commands = cp -f -r $$PWD_WIN/* $$DESTDIR_WIN
}
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

#----------------------------------------------------------------------------------------
# tworzenie instalatora offline
#----------------------------------------------------------------------------------------
INPUT = $$PWD/config/config.xml $$PWD/packages
offlineInstaller.depends = copydata
offlineInstaller.input = INPUT
offlineInstaller.output = $$INSTALLER_OFFLINE
offlineInstaller.commands = $$(QTDIR)/../../Tools/QtInstallerFramework/3.0/bin/binarycreator --offline-only -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}
offlineInstaller.CONFIG += target_predeps no_link combine
QMAKE_EXTRA_COMPILERS += offlineInstaller

#----------------------------------------------------------------------------------------
# tworzenie instalatora online
#----------------------------------------------------------------------------------------
INPUT = $$PWD/config/config.xml $$PWD/packages
onlineInstaller.depends = copydata
onlineInstaller.input = INPUT
onlineInstaller.output = $$INSTALLER_ONLINE
onlineInstaller.commands = $$(QTDIR)/../../Tools/QtInstallerFramework/3.0/bin/binarycreator --online-only -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}
onlineInstaller.CONFIG += target_predeps no_link combine
QMAKE_EXTRA_COMPILERS += onlineInstaller

#----------------------------------------------------------------------------------------
# po utworzeniu instalatorów
# tworzenie repozytoriów - tylko w trybie release
#----------------------------------------------------------------------------------------
CONFIG(release, debug|release) {
    INPUT = $$PWD/packages
    onlinePackages.depends = copydata
    onlinePackages.input = INPUT
    onlinePackages.output = $$PACKAGES_ONLINE
    onlinePackages.commands = $$(QTDIR)/../../Tools/QtInstallerFramework/3.0/bin/repogen -p $$PWD/packages -i $$quote(mac30.jak.installer) --update ${QMAKE_FILE_OUT}
    onlinePackages.CONFIG += target_predeps no_link combine
    QMAKE_EXTRA_COMPILERS += onlinePackages
}

#----------------------------------------------------------------------------------------
# pliki konfiguracyjne instalatora
#----------------------------------------------------------------------------------------
DISTFILES += \
    config/config.xml \
    packages/mac30.jak.installer/meta/package.xml \
    packages/mac30.jak.installer/data/readme.txt \
    config/installer_logo.png \
    config/installer_licon.png \
    config/installer_wicon.ico \
    packages/mac30.jak.installer/meta/installscript.qs

FORMS += \
    packages/mac30.jak.installer/meta/readmecheckboxform.ui
