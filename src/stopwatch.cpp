#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "stopwatch.hpp"

using namespace boost::posix_time;

namespace {

ptime now() {
	return microsec_clock::local_time();
}

}

stopwatch::stopwatch() { }
stopwatch::~stopwatch() { }

void stopwatch::start() {
	begin = now();
	end = ptime();
}

void stopwatch::stop() {
	end = now();
}

bool stopwatch::running() const {
	return (!begin.is_not_a_date_time()) && (end.is_not_a_date_time());
}

time_duration stopwatch::duration() const {
	if (begin.is_not_a_date_time()) return not_a_date_time;
	if (running()) return now() - begin;
	return end - begin;
}
