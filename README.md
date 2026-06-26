# competitive programming submission fetcher

![Python](https://img.shields.io/badge/Python-3.1-blue.svg)
![C++](https://img.shields.io/badge/C++-16.1-F34B7D.svg)
![Cmake](https://img.shields.io/badge/CMake-4.3-red.svg)

fetch all your submission from competitive programming platform and commit it on github

## highlights

* automated fetch all your submission with minimal setup
* simple and easy to setup and use
* detailed data (e.g ratings, tags, timestamp)
* commit for each submission with the original submit date to make your contribution graph looks magnificien
* automated git push to remote repository **- ongoing feature**

## architecture

'''bash
tui/                C++ FTXUI
backend/            python based backend service
shared/schema/      JSON contracts
cache/              caching
core/ main.py       markdwon generator
'''

## platforms

This tool currently support only [codeforces](https://codeforces.com/)

**soon :**
* [AtCoder](https://atcoder.jp/home)

integration with other platform are still in consideration. Contribution always welcomed

## instalation

before running the tools, make sure you have installed
- Python 3.10 or newer
- Git installed and avaible in PATH

if you want to make sure, follow the current command to verify :

```bash
python --version
git --version
```

**start the installation**
clone the repository :
```bash
git clone https://github.com/revvdn/codeforces_submission_scraper.git
```

move into the tools directory :
```bash
cd codeforcse_submission_scraper
```

install the required dependencies :
```bash
pip install -r requirements.txt
```

## getting started

after installing, run the following command to start :

build:
```bash
cmake -S, -B build
cmake --build build
```

run:
```bash 
./build/tui/cpse_tui
```

for windows, if python is not a real interpreter, set:

```powershell
$env:CPSE_PYTHON = "C:\path_to\python.exe"
```

## navigation
```text
TAB     : switch panel
ENTER   : fetch / analyze selected problem
UP/DOWN : navigate problem list
ESC     : return to list
Q       : quit / exit
```

## future work
1. **code complexity** - current code are having worst time complexity, but it can be improved later //DONE
2. **more platform support** - this quite complex because each platform has different method and need long time to breakdown
3. **submission analisys** - big feature under progress
4. **adding UI** - im curently work on Terminal UI (TUI) //PARTIALLY DONE
