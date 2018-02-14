# facerec-door-lock
Facial Recognition Door Lock Software for a Raspberry Pi 3 Model B with Raspberry Pi Camera Module v2, written in C++. This project is an adaptation/translation of Tony DiCola's [Raspberry Pi Face Recognition Software in Python](https://learn.adafruit.com/raspberry-pi-face-recognition-treasure-box?view=all). Re-creating the project in C++ was a result of outdated Python2/3 bindings for OpenCV 3.


Tested with: 
 - Raspberry Pi 3 Model B
 - Raspberry Pi Camera Module v2
 - OpenCV 3.4.0


### Virtual Environment
It is strongly recommended to use a Python virtual environment. To create a virtual env, use the `venv` feature of python3.
Run the command below in the root project directory. Recommended folder name for the virtual environment is `env`.
```
python3 -m venv <env-folder-name>
```

To activate that virtual environment, use the below command:
```
source <env-folder-name>/bin/activate
```

After activating, to install the dependencies run
```
pip3 install -r requirements.txt
```
