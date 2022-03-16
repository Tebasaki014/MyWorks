using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace Loopj
{
    class Player
    {
        static readonly float jumpSpeed = -6f;
        public float gravity = 0.08f;
        
        public Vector2 position = new Vector2(100, 480 - 128);
        public float yvelocity = 0f;

        Texture2D texture;
        public void SetTexture(Texture2D jikiTex)
        {
            this.texture = jikiTex; 
        }
        public void Update()
        {
            KeyboardState keyboard = Keyboard.GetState();
            position.Y = MathHelper.Clamp(position.Y, 0, 800 - 128);
            yvelocity += gravity;
            
            if (Button.IsDown())
            {
                yvelocity = jumpSpeed;
            }
            if (yvelocity > 0)
            {
                yvelocity = 1.5f;
            }
            position.Y += yvelocity;
        }
        public void Draw (SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(texture, position, Color.White);
        }
        public Rectangle GetHit()
        {
            return new Rectangle(
                (int)position.X + 10, (int)position.Y + 10,
                64 - 20, 64 - 20);
        }
        public void FinishUpdate()
        {
            position.X += 4;
        }
    }
}
