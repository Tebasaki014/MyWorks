// このファイルで必要なライブラリのnamespaceを指定
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using System.Collections.Generic;
using System;


/// <summary>
/// プロジェクト名がnamespaceとなります
/// </summary>
namespace Loopj
{

    enum State
    {
        Title,
        Play,
        Finish,
        Cleard,
        Died,
        Kusa,
        Sake,
        Mito,
    }
    /// <summary>
    /// ゲームの基盤となるメインのクラス
    /// 親クラスはXNA.FrameworkのGameクラス
    /// </summary>
    public class Game1 : Game
    {
        // フィールド（このクラスの情報を記述）
        private GraphicsDeviceManager graphicsDeviceManager;//グラフィックスデバイスを管理するオブジェクト
        private SpriteBatch spriteBatch;//画像をスクリーン上に描画するためのオブジェクト

        State state = State.Title;
        public static readonly int WindowWidth = 700;
        public static readonly int WindowHight = 600;

        Yuka yuka = new Yuka();
        Back back = new Back();
        Player player = new Player();
        Fufu fufu = new Fufu();
        private List<Iki> ikis;
        Teki teki = new Teki();
        private List<Teki> tekis;
        shi shi = new shi();
        kusa kusa = new kusa();
        Sake sake = new Sake();
        cleard cleard = new cleard();
        Title title = new Title();
        Mito mito = new Mito();
        private List<beer> beers;

        Texture2D texture6;
        Texture2D texture13;
        int mitoflag;
        int interval = 20;
        int beerCount = 0;

        Song nomal;
        Song boss;

        bool loop = true;

        Random random = new Random();

        /// <summary>
        /// コンストラクタ
        /// （new で実体生成された際、一番最初に一回呼び出される）
        /// </summary>
        /// 
        public Game1()
        {
            //グラフィックスデバイス管理者の実体生成
            graphicsDeviceManager = new GraphicsDeviceManager(this);
            //コンテンツデータ（リソースデータ）のルートフォルダは"Contentに設定
            Content.RootDirectory = "Content";
            graphicsDeviceManager.PreferredBackBufferWidth = WindowWidth;
            graphicsDeviceManager.PreferredBackBufferHeight = WindowHight;
        }

        /// <summary>
        /// 初期化処理（起動時、コンストラクタの後に1度だけ呼ばれる）
        /// </summary>
        protected override void Initialize()
        {
            // この下にロジックを記述
            tekis = new List<Teki>();
            beers = new List<beer>();
            ikis = new List<Iki>();
           
            for (int i = 0; i < 30; i++)
            {
                tekis.Add(new Teki());
            }

            //beers.Add(new beer(texture6, mito.Kuchipo()));

            for (int i = 0; i < tekis.Count; i++)
            {
                int hoge = 200 * (i+1);
                int x = 900 + hoge;

                int y = 0;

                int r = random.Next(4);

                if (r == 0) { y = 0; }
                if (r == 1) { y = 150; }
                if (r == 2) { y = 300; }
                if (r == 3) { y = 450; }

                tekis[i].Initialize(x, y);
            }

            mito.Initialize();

            player.position = new Vector2(100, 480 - 128);

            beerCount = 0;
            interval = 60;
            // この上にロジックを記述
            base.Initialize();// 親クラスの初期化処理呼び出し。絶対に消すな！！
        }

        /// <summary>
        /// コンテンツデータ（リソースデータ）の読み込み処理
        /// （起動時、１度だけ呼ばれる）
        /// </summary>
        protected override void LoadContent()
        {
            // 画像を描画するために、スプライトバッチオブジェクトの実体生成
            spriteBatch = new SpriteBatch(GraphicsDevice);

            // この下にロジックを記述
            Texture2D texture = Content.Load<Texture2D>("Leaf");
            yuka.SetTexture(texture);
            Texture2D texture2 = Content.Load<Texture2D>("paplane");
            player.SetTexture(texture2);
            Texture2D texture3 = Content.Load<Texture2D>("cyclone");
            foreach(Teki e in tekis)
            {
                e.SetTexture(texture3);
            }
            Texture2D texture4 = Content.Load<Texture2D>("shi");
            shi.SetTexture(texture4);
            Texture2D texture5 = Content.Load<Texture2D>("mozamito");
            mito.SetTexture(texture5);
            texture6 = Content.Load<Texture2D>("beer");
            Texture2D texture7 = Content.Load<Texture2D>("kami");
            cleard.SetTexture(texture7);
            Texture2D texture8 = Content.Load<Texture2D>("title");
            title.SetTexture(texture8);
            Texture2D texture9 = Content.Load<Texture2D>("kusa");
            kusa.SetTexture(texture9);
            Texture2D texture10 = Content.Load<Texture2D>("sake");
            sake.SetTexture(texture10);
            Texture2D texture11 = Content.Load<Texture2D>("kabe");
            back.SetTexture(texture11);
            Texture2D texture12 = Content.Load<Texture2D>("fufukao");
            fufu.SetTexture(texture12);
            texture13 = Content.Load<Texture2D>("fufuiki");

            boss = Content.Load<Song>("3_strength_and_discipline");
            nomal = Content.Load<Song>("famipop3");

            // この上にロジックを記述
        }

        /// <summary>
        /// コンテンツの解放処理
        /// （コンテンツ管理者以外で読み込んだコンテンツデータを解放）
        /// </summary>
        protected override void UnloadContent()
        {
            // この下にロジックを記述


            // この上にロジックを記述
        }

        /// <summary>
        /// 更新処理
        /// （1/60秒の１フレーム分の更新内容を記述。音再生はここで行う）
        /// </summary>
        /// <param name="gameTime">現在のゲーム時間を提供するオブジェクト</param>
        protected override void Update(GameTime gameTime)
        {
            // ゲーム終了処理（ゲームパッドのBackボタンかキーボードのエスケープボタンが押されたら終了）
            if ((GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed) ||
                 (Keyboard.GetState().IsKeyDown(Keys.Escape)))
            {
                Exit();
            }

            KeyState.Update();
            // この下に更新ロジックを記述

            Button.Update();
            
            foreach(Iki e in ikis)
            {
                e.Update();
            }
            ikis.RemoveAll(e => e.IsRemove());
            if(Button.IsDown())
            {
                ikis.Add(new Iki(texture13));
            }

            if (state == State.Title)
            {
                back.Update();
                yuka.Update();

                if (Button.IsDown())
                {
                    state = State.Play;
                }
            }
            if (state == State.Play)
            {
                if (MediaPlayer.State != MediaState.Playing)
                {
                    MediaPlayer.Play(nomal);
                }
                foreach(Teki e in tekis)
                {
                    e.Update();
                }
                back.Update();
                yuka.Update();
                player.Update();
                if (IsHit() == true)
                {
                    MediaPlayer.Stop();
                    state = State.Died;
                    Initialize();
                }
                if (IsKusa() == true)
                {
                    MediaPlayer.Stop();
                    state = State.Kusa;
                    Initialize();
                }
                if (Ismito() == true)
                {
                    MediaPlayer.Stop();
                    state = State.Mito;
                }
            }
            if(state == State.Mito)
            {
                if (MediaPlayer.State != MediaState.Playing)
                {
                    MediaPlayer.Play(boss);
                }
                MediaPlayer.IsRepeating = loop;

                interval--;
                back.Update();
                yuka.Update();
                player.Update();
                mito.Update();
                foreach(beer e in beers)
                {
                    e.Update();
                }
                beers.RemoveAll(e => e.IsRemove());

                if (mito.Standby() == true && interval <= 0) 
                {
                    beers.Add(new beer(texture6, mito.Kuchipo()));
                    interval = 90;
                    beerCount++;
                }

                if (IsHit() == true)
                {
                    MediaPlayer.Stop();
                    state = State.Died;
                    Initialize();
                }
                if(IsKusa() == true)
                {
                    MediaPlayer.Stop();
                    state = State.Kusa;
                    Initialize();
                }
                if (IsSake() == true)
                {
                    MediaPlayer.Stop();
                    state = State.Sake;
                    Initialize();
                }

                if (beerCount >= 8)
                {
                    state = State.Finish;
                }
            }
            if(state == State.Finish)
            {
                back.Update();
                yuka.Update();
                player.FinishUpdate();
                mito.FinishUpdate();
                foreach (beer e in beers)
                {
                    e.Update();
                }

                if (player.position.X >= 1000)
                {
                    state = State.Cleard;
                    Initialize();
                }
            }
            if(state == State.Cleard)
            {
                MediaPlayer.Stop();

                interval--;


                if (Button.IsDown() && interval <= 0)
                {
                    state = State.Title;
                    Initialize();
                }
            }
            if(state == State.Died)
            {
                interval--;


                if (Button.IsDown() && interval <= 0) 
                {
                    state = State.Title;
                    Initialize();
                }
            }
            if (state == State.Kusa)
            {
                interval--;


                if (Button.IsDown() && interval <= 0)
                {
                    state = State.Title;
                    Initialize();
                }
            }
            if (state == State.Sake)
            {
                interval--;


                if (Button.IsDown() && interval <= 0)
                {
                    state = State.Title;
                    Initialize();
                }
            }


            // この上にロジックを記述
            base.Update(gameTime); // 親クラスの更新処理呼び出し。絶対に消すな！！
        }

        /// <summary>
        /// 描画処理
        /// </summary>
        /// <param name="gameTime">現在のゲーム時間を提供するオブジェクト</param>
        /// 
        bool IsHit()
        {
            Rectangle playerHit = player.GetHit();
            foreach (Teki e in tekis)
            {
                if (e.GetHit().Intersects(playerHit)) return true;
            } 
            return false;
        }
        bool IsKusa()
        {
            if (player.position.Y > WindowHight - 64) return true;
            return false;
        }
        bool IsSake()
        {
            foreach (beer e in beers)
            {
                Rectangle playerHit = player.GetHit();
                if (e.GetHit().Intersects(playerHit) && mito.Standby() == true) return true;
            }
            return false;
        }
        protected override void Draw(GameTime gameTime)
        {
            // 画面クリア時の色を設定

            GraphicsDevice.Clear(Color.Gray);

            // この下に描画ロジックを記述
            spriteBatch.Begin();
            back.Draw(spriteBatch);
            fufu.Draw(spriteBatch);
            foreach(Iki e in ikis)
            {
                e.Draw(spriteBatch);
            }
            player.Draw(spriteBatch);
            yuka.Draw(spriteBatch);

            if (state == State.Mito || state == State.Finish)
            {
                mito.Draw(spriteBatch);
            }
            if(mito.Standby() == true || state == State.Finish)
            {
                foreach(beer e in beers)
                {
                    e.Draw(spriteBatch);
                }
            }

            foreach (Teki e in tekis)
            {
                e.Draw(spriteBatch);
            }
            
            if(state == State.Title)
            {
                title.Draw(spriteBatch);
            }
            if(state == State.Died)
            {
                shi.Draw(spriteBatch);
            }
            if(state == State.Kusa)
            {
                kusa.Draw(spriteBatch);
            }
            if(state == State.Sake)
            {
                sake.Draw(spriteBatch);
            }
            if(state == State.Cleard)
            {
                cleard.Draw(spriteBatch);
            }
            spriteBatch.End();
            //この上にロジックを記述
            base.Draw(gameTime); // 親クラスの更新処理呼び出し。絶対に消すな！！
        }
        bool Ismito()
        {
            mitoflag = tekis.Count - 1;
            if (tekis[mitoflag].position.X <= -64)
            {
                return true;
            }
            else return false;            
        }
    }
}
