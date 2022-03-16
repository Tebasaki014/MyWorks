using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
namespace Loopj
{
    class Yuka
    {
        public static readonly int yukaHeight = 64;
        public static readonly int yukaWidth = 64;
        public static readonly float speed = 5f;

        float yukaX = 0f;
        Texture2D texture;
        public void SetTexture(Texture2D yukaTex)
        {
            this.texture = yukaTex;
        }
        public void Update()
        {
            yukaX += speed;
        }
        public void Draw(SpriteBatch spriteBatch)
        {
            float y = 600 - yukaHeight;
            float x = yukaX % yukaWidth;

            for (int i=0; i < 16; i++)
            {
                spriteBatch.Draw(texture, new Vector2(yukaWidth * i - x, y), Color.White);
            }
        }
        public Rectangle GetHit()
        {
            return new Rectangle((int)yukaWidth + 15, (int)yukaHeight + 15,
                64 - 30, 64 - 30);
        }
    }
}
