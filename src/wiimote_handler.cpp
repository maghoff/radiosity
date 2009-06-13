#include <iostream>
#include <boost/thread.hpp>
#include <cwiid.h>
#include "wiimote_handler.hpp"

void test_cwiid() {
	std::cout << "Connecting..." << std::endl;

	bdaddr_t addr = *BDADDR_ANY;
	cwiid_wiimote_t *r = cwiid_connect(&addr, 0);

	std::cout << "wiimote handle: " << r << std::endl;

	if (r) cwiid_disconnect(r);
}


struct wiimote_handler::impl {
	boost::thread t;

	impl();
	~impl();
};

wiimote_handler::impl::impl() //:
//	t(&test_cwiid)
{
}

wiimote_handler::impl::~impl() { }

wiimote_handler::wiimote_handler() :
	d(new impl)
{
	test_cwiid();
}

wiimote_handler::~wiimote_handler() {
	d->t.join();
}
