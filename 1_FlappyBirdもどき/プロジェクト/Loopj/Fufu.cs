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
    class Fufu
    {
        public Vector2 position;
        public Texture2D texture;
        public Fufu()
        {
            position = new Vector2(-30, 600 - 115 - 64);
        }
        public void SetTexture(Texture2D texture)
        {
            this.texture = texture;
        }
        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(texture, position, Color.White);
        }
    }
}
