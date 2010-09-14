/*!
    @file   KRParticle2DSystem.h
    @author numata
    @date   09/08/07
 
    Please write the description of this class.
 */

#pragma once

#include <Karakuri/Karakuri.h>


#define KR_PARTICLE2D_USE_POINT_SPRITE  0


struct _KRParticle2DGenInfo_old {
    KRVector2D  centerPos;
    int         count;
};


const int _KRParticle2DGenMaxCount_old = 20;


class _KRParticle2D_old : public KRObject {
    
public:
    unsigned    mLife;
    unsigned    mBaseLife;
    KRVector2D  mPos;
    KRVector2D  mV;
    KRVector2D  mGravity;
    KRColor     mColor;
    double      mSize;
    
    double      mDeltaSize;
    double      mDeltaRed;
    double      mDeltaGreen;
    double      mDeltaBlue;
    double      mDeltaAlpha;
    
public:
	_KRParticle2D_old(unsigned life, const KRVector2D& pos, const KRVector2D& v, const KRVector2D& gravity, const KRColor& color, double size,
                  double deltaRed, double deltaGreen, double deltaBlue, double deltaAlpha, double deltaSize);
    
public:
    bool    step();
    
public:
    virtual std::string to_s() const;

};

/*!
    @class  KRParticle2DSystem
    @group  Game Graphics
    @abstract   <strong class="warning">(Deprecated) 現在、このクラスの利用は推奨されません。代わりに、Karakuri Box と gKRAnime2DMan を利用してください。</strong>
    <p>2次元の移動を行うパーティクル群を生成し管理するための仕組みです。<br/>
    火、爆発、煙、雲、霧などの表現に利用できます。</p>
 */
class KRParticle2DSystem : public KRObject {
    
    std::list<_KRParticle2D_old*>   mParticles;

    unsigned        mLife;
    KRVector2D      mStartPos;
    
    KRTexture2D*    mTexture;
    bool            mHasInnerTexture;
    
    KRVector2D      mMinV;
    KRVector2D      mMaxV;
    KRVector2D      mGravity;
    
    unsigned        mParticleCount;
    int             mGenerateCount;
    
    KRBlendMode     mBlendMode;
    
    KRColor         mColor;
    double          mDeltaSize;
    double          mDeltaRed;
    double          mDeltaGreen;
    double          mDeltaBlue;
    double          mDeltaAlpha;
    
    bool            mDoLoop;
    _KRParticle2DGenInfo_old    mGenInfos[_KRParticle2DGenMaxCount_old];
    int             mActiveGenCount;
    
#if KR_PARTICLE2D_USE_POINT_SPRITE
    double          mSize;
#else
    double          mMinSize;
    double          mMaxSize;
#endif
    
public:
    /*!
        @task コンストラクタ
     */
    
    /*!
        @method KRParticle2DSystem
        @abstract テクスチャに使用する画像ファイルの名前を指定して、このパーティクル・システムを生成します。
        <p>デフォルトでは、addGenerationPoint() 関数を用いて、単発生成を行います。</p>
        <p>doLoop 引数に true を指定することで、パーティクルを無限に生成し続けるようになります。</p>
     */
    KRParticle2DSystem(const std::string& filename, bool doLoop=false);

    /*!
        @method KRParticle2DSystem
        @abstract テクスチャを指定して、このパーティクル・システムを生成します。
        <p>このコンストラクタを利用することにより、同じテクスチャを異なる複数のパーティクル・システムで共有して効率的に使うことができます。同じ画像でサイズが異なるパーティクルを生成したい場合などに、このコンストラクタを利用してください。</p>
        <p>デフォルトでは、addGenerationPoint() 関数を用いて、単発生成を行います。</p>
        <p>doLoop 引数に true を指定することで、パーティクルを無限に生成し続けるようになります。</p>
     */
    KRParticle2DSystem(KRTexture2D* texture, bool doLoop=false);
    virtual ~KRParticle2DSystem();
    
private:
    void    init();
    
public:
    /*!
        @task 実行のための関数
     */
    
    /*!
        @method draw
        このパーティクル・システムで生成されたすべてのパーティクルを描画します。
     */
    void    draw();
    
    /*!
        @method step
        設定に基づいて必要なパーティクルを生成し、生成されたすべてのパーティクルを動かします。基本的に、1フレームに1回この関数を呼び出してください。
     */
    void    step();

public:
    /*!
        @task ループ実行のための関数
     */
    
    /*!
        @method getStartPos
        ループ実行時のパーティクルの生成時の位置を取得します。
     */
    KRVector2D  getStartPos() const;
    
    /*!
        @method setStartPos
        ループ実行時のパーティクルの生成時の位置を設定します。
     */
    void    setStartPos(const KRVector2D& pos);
    
public:
    /*!
        @task 単発実行のための関数
     */
    
    /*!
        @method addGenerationPoint
        @abstract 新しいパーティクル生成ポイントを指定された座標に追加します。
        setParticleCount() 関数で設定された最大個数だけパーティクルを生成した時点で、その生成ポイントは削除されます。
     */
    void    addGenerationPoint(const KRVector2D& pos);

public:
    /*!
        @task 設定のための関数
     */

    /*!
        @method setBlendMode
        @abstract パーティクルを描画するためのブレンドモードを設定します。
        デフォルトのブレンドモードは、KRBlendModeAddition に設定されています。
     */
    void    setBlendMode(KRBlendMode blendMode);
    
    /*!
        @method setColor
        パーティクル描画時に適用される初期カラーを設定します。
     */
    void    setColor(const KRColor& color);
    
    /*!
        @method setColorDelta
        パーティクルの生存期間の割り合い（0.0〜1.0）に応じた、各色成分の変化の割り合いを設定します。
     */
    void    setColorDelta(double red, double green, double blue, double alpha);
    
    /*!
        @method setGenerateCount
        @abstract 1フレーム（1回の step() 関数呼び出し）ごとのパーティクルの最大生成個数を設定します。
        マイナスの値を設定すると、それ以降パーティクルは生成されなくなります。
     */
    void    setGenerateCount(int count);
    
    /*!
        @method setGravity
        @abstract 各パーティクルの1フレーム（1回の step() 関数呼び出し）ごとに適用される加速度を設定します。
        デフォルトでは加速度は (0.0, 0.0) に設定されています。
     */
    void    setGravity(const KRVector2D& a);
    
    /*!
        @method setLife
        @abstract 各パーティクルの生存期間を設定します。
        既に生成されているパーティクルには影響を及ぼしません。デフォルトの生存期間は、60フレーム（=1秒）です。
     */
    void    setLife(unsigned life);
    
    /*!
        @method setMaxV
        @abstract パーティクル生成時にランダムで設定される移動速度の最大値を設定します。
     */
    void    setMaxV(const KRVector2D& v);
    
    /*!
        @method setMinV
        @abstract パーティクル生成時にランダムで設定される移動速度の最小値を設定します。
     */
    void    setMinV(const KRVector2D& v);
    
    /*!
        @method setParticleCount
        @abstract パーティクルの最大個数を設定します。
        デフォルトの設定では256個です。
     */
    void    setParticleCount(unsigned count);
    
    /*!
        @method setSizeDelta
        パーティクルの生存期間の割り合い（0.0〜1.0）に応じた、サイズの変化の割り合いを設定します。
     */
    void    setSizeDelta(double value);
    
#if KR_PARTICLE2D_USE_POINT_SPRITE
    void    setSize(double size);
#else
    /*!
        @method setMaxSize
        各パーティクルの生成時の最大サイズを設定します。
     */
    void    setMaxSize(double size);

    /*!
        @method setMinSize
        各パーティクルの生成時の最小サイズを設定します。
     */
    void    setMinSize(double size);    
#endif
    
public:
    /*!
        @task 現在の設定確認のための関数
     */
    
    /*!
        @method getBlendMode
        @abstract パーティクルを描画するためのブレンドモードを取得します。
     */
    KRBlendMode getBlendMode() const;
    
    /*!
        @method getColor
        @abstract パーティクル描画時に適用される初期カラーを取得します。
     */
    KRColor     getColor() const;

    /*!
        @method getDeltaAlpha
        @abstract パーティクルの生存期間の割り合い（0.0〜1.0）に応じたアルファ成分の変化の割り合いを取得します。
     */
    double      getDeltaAlpha() const;

    /*!
        @method getDeltaBlue
        @abstract パーティクルの生存期間の割り合い（0.0〜1.0）に応じた青成分の変化の割り合いを取得します。
     */
    double      getDeltaBlue() const;

    /*!
        @method getDeltaGreen
        @abstract パーティクルの生存期間の割り合い（0.0〜1.0）に応じた緑成分の変化の割り合いを取得します。
     */
    double      getDeltaGreen() const;

    /*!
        @method getDeltaRed
        @abstract パーティクルの生存期間の割り合い（0.0〜1.0）に応じた赤成分の変化の割り合いを取得します。
     */
    double      getDeltaRed() const;
    
    /*!
        @method getDeltaSize
        @abstract パーティクルの生存期間の割り合い（0.0〜1.0）に応じたサイズの変化の割り合いを取得します。
     */
    double      getDeltaSize() const;
    
    /*!
        @method getGenerateCount
        @abstract 1フレーム（1回の step() 関数呼び出し）ごとのパーティクルの最大生成個数を取得します。
     */
    int         getGenerateCount() const;
    
    /*!
        @method getGeneratedParticleCount
        @abstract 現時点で生成されているパーティクルの個数を取得します。
     */
    unsigned    getGeneratedParticleCount() const;
    
    /*!
        @method getGravity
        @abstract 各パーティクルの1フレーム（1回の step() 関数呼び出し）ごとに適用される加速度を取得します。
     */
    KRVector2D  getGravity() const;
    
    /*!
        @method getLife
        @abstract 各パーティクルの生存期間を取得します。
     */
    unsigned    getLife() const;
    
    /*!
        @method getMaxV
        @abstract パーティクル生成時にランダムで設定される移動速度の最大値を取得します。
     */
    KRVector2D  getMaxV() const;
    
    /*!
        @method getMinV
        @abstract パーティクル生成時にランダムで設定される移動速度の最小値を取得します。
     */
    KRVector2D  getMinV() const;
    
    /*!
        @method getParticleCount
        @abstract パーティクルの最大個数を取得します。
     */
    unsigned    getParticleCount() const;
    
public:
#if KR_PARTICLE2D_USE_POINT_SPRITE
    double      getSize() const;
#else
    /*!
        @method getMaxSize
        @abstract 各パーティクルの生成時の最大サイズを取得します。
     */
    double      getMaxSize() const;
    
    /*!
        @method getMinSize
        @abstract 各パーティクルの生成時の最小サイズを取得します。
     */
    double      getMinSize() const;
#endif
    
public:
    virtual std::string to_s() const;

};

