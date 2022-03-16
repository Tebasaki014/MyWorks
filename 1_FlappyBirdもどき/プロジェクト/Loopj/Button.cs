using Microsoft.Xna.Framework.Input;

namespace Loopj
{
    static class Button
    {
        static KeyboardState State; 
        static KeyboardState prevState; 

        public static void Update()
        {
            prevState = State;
            State = Keyboard.GetState();
        }

        public static bool IsDown()
        {
            return State.IsKeyDown(Keys.Space) && prevState.IsKeyUp(Keys.Space);
        }
    }
}
