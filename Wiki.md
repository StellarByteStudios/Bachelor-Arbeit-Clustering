# Wikis
## Git Setup
1) agend für ssh starten `eval $(ssh-agent -s)`
2) schauen ob ssh-Key vorhanden ist `cd ~/.ssh/ && ls`
3) **Falls Key nicht vorhanden:** 
    5) In ssh-Ordner gehen `cd ~/.ssh/ && ls`
    5) `ssh-keygen -t ed25519 -C "krollmann.carsten@gmail.com"`
4) code holen und kopieren `cat ~/.ssh/id_ed25519.pub` (oder anderes Keyfile)
5) In richtigen Ordner gehen
6) in User-Einstellungen ssh-key mit gutem Namen anlegen
    7) Github: Profil -> Settings -> SSH und GPG keys -> SSH keys (New SSH key)
    8) GitLab: Profilbild -> Edit Profile -> SSH Keys -> Your SSH keys (Add new key)
8) Verbindung Testen mit `ssh -T git@gitlab.cs.uni-duesseldorf.de` oder `ssh -T git@github.com`

## Github Desktop mit Sync
1) In vernünftigen Downloadordner gehen
2) Download: `sudo wget https://github.com/shiftkey/desktop/releases/download/release-3.1.1-linux1/GitHubDesktop-linux-3.1.1-linux1.deb`
3) Install: `sudo dpkg -i GitHubDesktop-linux-3.1.1-linux1.deb`
4) Sync der Repos
    5) Beide Repos händisch klonen über SSH in geeignete Ordner
    6) in beiden Repos die Datei in `Repo/.git/config` öffnen
    7) in die GitHub Config den Abschnitt unter `[remote "origin"]` den Teil von GitLab kopieren
8) Das Github Repo mit GitHub-Desktop öffnen






