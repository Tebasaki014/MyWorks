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
    class Rogo
    {
        protected Vector2 position;
        protected Texture2D texture;

        public void SetTexture(Texture2D texture)
        {
            this.texture = texture;
        }
        public void Initialize()
        {
            position = new Vector2(0, 0);
        }
        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(texture, position, Color.White);
        }
    }
}
