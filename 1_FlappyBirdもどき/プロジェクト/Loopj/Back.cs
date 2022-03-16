using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace Loopj
{
    class Back
    {
        public static readonly int Height = Game1.WindowHight;
        public static readonly int Width = Game1.WindowWidth;
        public static readonly float speed = 5f;

        float X = 0f;
        Texture2D texture;
        public void SetTexture(Texture2D texture)
        {
            this.texture = texture;
        }
        public void Update()
        {
            X += speed;
        }
        public void Draw(SpriteBatch spriteBatch)
        {
            float y = 600 - Height;
            float x = X % Width;

            for (int i = 0; i < 2; i++)
            {
                spriteBatch.Draw(texture, new Vector2((Width -10) * i - x, y), Color.White);
            }
        }
    }
}
