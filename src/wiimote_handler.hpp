#ifndef SIMPLEMODEL_WIIMOTE_HANDLER_HPP
#define SIMPLEMODEL_WIIMOTE_HANDLER_HPP

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

class wiimote_handler : public boost::noncopyable {
	struct impl;
	boost::scoped_ptr<impl> d;

public:
	wiimote_handler();
	virtual ~wiimote_handler();


};

#endif
