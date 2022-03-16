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
    class Iki
    {
        public Vector2 position;
        public float speed;
        public Texture2D texture;
        
        public Iki(Texture2D texture)
        {
            this.texture = texture;
            position = new Vector2(-30, 600 - 115 - 64);
            speed = -5f;
        }
        public void Update()
        {
            position.Y += speed;
        }
        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(texture, position, Color.White);
        }
        public bool IsRemove()
        {
            if (position.Y < 350)
            {
                return true;
            }
            else return false;
        }
    }
}
