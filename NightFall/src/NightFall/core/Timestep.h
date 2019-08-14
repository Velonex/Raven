#pragma once

namespace nfe {

	class Timestep {
	public:
		Timestep(float time = 0.0f) : _time(time) {

		}
		float getSeconds() const { return _time; }
		float getMilliSeconds() const { return _time * 1000.f; }

	private:
		float _time = 0.0f;
	};

}