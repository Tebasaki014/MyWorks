using Microsoft.Xna.Framework.Input;

namespace Loopj
{
    class KeyState
    {
        static KeyboardState State;
        static KeyboardState prev;

        public static void Update() 
        {
            prev = State;
            State = Keyboard.GetState();
        }
        public  static bool IsJunpkeyDown()
        {
            return State.IsKeyDown(Keys.Space) && prev.IsKeyUp(Keys.Space);
        }
    }
}
