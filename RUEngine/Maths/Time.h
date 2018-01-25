#ifndef TIME_H
#define TIME_H

#include <iostream>
#include "glfw3.h"
class Time
{
    public:
        Time();
        virtual ~Time();
        float getDeltatime();
        int getFPS();
        void update();
        struct Timer {
        public:
		  void init() { timerStartTime = 0.0f; timerCurrentTime = 0.0f; }
          void start() { timerStartTime = glfwGetTime(); }
          void stop() { timerCurrentTime = 0.0f; }
          float seconds() { timerCurrentTime = glfwGetTime(); return timerCurrentTime - timerStartTime; }
        private:
          float timerStartTime;
          float timerCurrentTime;
        };
        Timer timer;
    private:
      float dt;
      float currentTime,
            previousTime,
            lastTime = 0;
      int fps;


};

#endif // TIME_H
