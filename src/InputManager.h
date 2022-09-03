#pragma once

#include "Types.h"

namespace RenEngine
{
    class InputManager
    {
        public:
            //  Some common keyboard buttons for games
            enum input_codes
            {
                unknown = -1,

                left_shift = 340,
                left_ctrl,
                left_alt,
                
                space = 32,

                num_0 = 48,
                num_2,
                num_3,
                num_4,
                num_5,
                num_6,
                f1 = 290,
                f2,
                f3,
                f4,

                w = 87,
                a = 65,
                s = 83,
                d = 68,

                escape = 256,
                enter,
                tab,

            };

            void imStartup();
            void imShutdown();

            void update();
            bool keyPressed(GraphicsManager&, input_codes);
    };
}