using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace Loopj
{
    class Mito
    {
        public Vector2 position;
        public Vector2 kuchi;
        public float speed;
        public Vector2 buruburu;
        public Texture2D texture;

        public void SetTexture(Texture2D texture)
        {
            this.texture = texture;
        }
        public void Initialize()
        {
            position = new Vector2(900, 50);
            speed = 2.0f;
            buruburu = new Vector2(2, 15);
        }
        public void Update()
        {

            if (Standby() == false)
            {
                position.X -= speed;
            }
            if (Standby() == true)
            {
                position.Y += speed;
                if(position.Y <= -50 || position.Y>= 400)
                {
                    speed *= -1;
                }
            }
        }
        public void FinishUpdate()
        {
            position += buruburu;
            buruburu.Y *= -1;
        }
        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(texture, position, Color.White);
        }
        public Vector2 Kuchipo()
        {
            kuchi = new Vector2(position.X + 90, position.Y + 150);
            return kuchi;
        }
        public bool Standby()
        {
            if (position.X <= 400)
            {
                return true;
            }
            else return false;
        }
    }
}
