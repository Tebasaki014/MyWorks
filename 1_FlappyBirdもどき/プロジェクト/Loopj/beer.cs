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
    class beer
    {
        public Vector2 position;
        public Vector2 direction;
        public Texture2D texture;

        Random random = new Random();

        public beer(Texture2D texture, Vector2 position)
        {
            this.texture = texture;
            this.position = position;
        }
        public void Update()
        {
            int r = random.Next(5);
            if (r == 0) { direction = new Vector2(-4, 32); }
            if (r == 1) { direction = new Vector2(-4, 16); }
            if (r == 2) { direction = new Vector2(-4, 0); }
            if (r == 3) { direction = new Vector2(-4, -8); }
            if (r == 0) { direction = new Vector2(-4, -16); }

            position += direction;

        }
        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(texture, position, Color.White);
        }
        public Rectangle GetHit()
        {
            return new Rectangle((int)position.X + 15, (int)position.Y + 15,
                64 - 30, 64 - 30);
        }
        public bool IsRemove()
        {
            if (position.X < -64)
            {
                return true;
            }
            else return false;
        }
    }
}
