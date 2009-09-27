#ifndef SIMPLEMODEL_STOPWATCH_HPP
#define SIMPLEMODEL_STOPWATCH_HPP

#include <boost/date_time/posix_time/posix_time_types.hpp>

class stopwatch {
	boost::posix_time::ptime begin, end;
public:
	stopwatch();
	~stopwatch();

	void start();
	void stop();

	bool running() const;
	boost::posix_time::time_duration duration() const;
};

#endif // SIMPLEMODEL_STOPWATCH_HPP
