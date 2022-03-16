﻿#pragma once
struct Easings
{
	//序盤速く、徐々に減速
	static float EaseOutQuad(float timeRate);

	//序盤遅く、徐々に加速
	static float EaseInQuad(float timeRate);

	//序盤遅く、中盤速く、終盤減速
	static float EaseInOutQuad(float timeRate);

	//序盤速く、徐々に減速
	static float EaseOutCubic(float timeRate);

	//序盤遅く、徐々に加速
	static float EaseInCubic(float timeRate);

	//序盤遅く、中盤速く、終盤減速
	static float EaseInOutCubic(float timeRate);

	//序盤速く、徐々に減速
	static float EaseOutQuart(float timeRate);

	//序盤遅く、徐々に加速
	static float EaseInQuart(float timeRate);

	//序盤遅く、中盤速く、終盤減速
	static float EaseInOutQuart(float timeRate);

	//序盤速く、徐々に減速
	static float EaseOutQuint(float timeRate);

	//序盤遅く、徐々に加速
	static float EaseInQuint(float timeRate);

	//序盤遅く、中盤速く、終盤減速
	static float EaseInOutQuint(float timeRate);

	//序盤速く、徐々に減速
	static float EaseOutExpo(float timeRate);

	//序盤遅く、徐々に加速
	static float EaseInExpo(float timeRate);

	//序盤遅く、中盤速く、終盤減速
	static float EaseInOutExpo(float timeRate);

	//一度目標値を通り過ぎてから戻る
	static float EaseOutBack(float timeRate, float over);

	//逆走してから一気に動く
	static float EaseInBack(float timeRate, float over);

	//逆走してから一気に動き、一度目標値を通り過ぎてから戻る
	static float EaseInOutBack(float timeRate, float over);

	//目標値でバウンド
	static float EaseOutBounce(float timeRate);

	//目標値でバネみたいになる
	static float EaseOutElastic(float timeRate, float over, float period);
};

/*ライセンス
Terms of Use: Easing Functions (Equations)
Open source under the MIT License and the 3-Clause BSD License.

MIT License
Copyright © 2001 Robert Penner

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

BSD License
Copyright © 2001 Robert Penner

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of the author nor the names of contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/