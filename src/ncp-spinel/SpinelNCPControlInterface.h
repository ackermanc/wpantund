/*
 *
 * Copyright (c) 2016 Nest Labs, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef __WPAN_DUMMY_NCP_H__
#define __WPAN_DUMMY_NCP_H__ 1

#include "NCPInstance.h"
#include "NCPControlInterface.h"
#include "nlpt.h"
#include "Callbacks.h"
#include "EventHandler.h"

#include <queue>
#include <set>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace nl {
namespace wpantund {

class SpinelNCPInstance;

class SpinelNCPControlInterface : public NCPControlInterface {
public:
	friend class SpinelNCPInstance;

	SpinelNCPControlInterface(SpinelNCPInstance* instance_pointer);
	virtual ~SpinelNCPControlInterface() { }

	virtual const WPAN::NetworkInstance& get_current_network_instance(void)const;

	virtual void join(
		const ValueMap& options,
	    CallbackWithStatus cb = NilReturn()
	);

	virtual void form(
		const ValueMap& options,
	    CallbackWithStatus cb = NilReturn()
	);

	virtual void leave(CallbackWithStatus cb = NilReturn());
	virtual void attach(CallbackWithStatus cb = NilReturn());
	virtual void begin_low_power(CallbackWithStatus cb = NilReturn());

	virtual void netscan_start(const ValueMap& options, CallbackWithStatus cb = NilReturn());
	virtual void netscan_stop(CallbackWithStatus cb = NilReturn());

	virtual void begin_net_wake(uint8_t data, uint32_t flags, CallbackWithStatus cb = NilReturn());
	virtual void reset(CallbackWithStatus cb = NilReturn());
	virtual void permit_join(
	    int seconds = 15 * 60,
	    uint8_t commissioning_traffic_type = 0xFF,
	    in_port_t commissioning_traffic_port = 0,
	    bool network_wide = false,
	    CallbackWithStatus      cb = NilReturn());

	virtual void refresh_state(CallbackWithStatus cb = NilReturn());

	virtual void get_property(
	    const std::string& key, CallbackWithStatusArg1 cb);
	virtual void set_property(
	    const std::string&                      key,
	    const boost::any&                       value,
	    CallbackWithStatus      cb);
	virtual void config_gateway(bool defaultRoute, const uint8_t prefix[8], uint32_t preferredLifetime, uint32_t validLifetime, CallbackWithStatus cb = NilReturn());
	virtual void add_external_route(const uint8_t route[], int route_prefix_len, int domain_id, ExternalRoutePriority priority, CallbackWithStatus);
	virtual void remove_external_route(const uint8_t route[], int route_prefix_len, int domain_id, CallbackWithStatus cb);

	virtual void data_poll(CallbackWithStatus cb = NilReturn());
	virtual void host_did_wake(CallbackWithStatus cb = NilReturn());

	virtual std::string get_name();

	virtual NCPInstance& get_ncp_instance(void);

private:

	SpinelNCPInstance* mNCPInstance;

};

}; // namespace wpantund
}; // namespace nl


#endif
