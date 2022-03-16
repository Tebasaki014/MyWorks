using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

using System;

namespace Loopj
{
    class Teki
    {
        public int ppox;
        public int ppoy;
        public Vector2 position;
        Texture2D texture;
        float speed;
        

        public Teki()
        {
            
            speed = 5.0f;
        }
        public void Initialize(int posX, int posY)
        {
            ppox = posX;
            ppoy = posY;
            position = new Vector2(ppox, ppoy);
        }
        public void SetTexture(Texture2D tekiTex)
        {
            this.texture = tekiTex;
        }
        public void Update()
        {
            speed = 5f;
            position.X -= speed;
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
    }
}
