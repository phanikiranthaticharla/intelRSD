/*!
 * @section LICENSE
 *
 * @copyright
 * Copyright (c) 2015-2018 Intel Corporation
 *
 * @copyright
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * @copyright
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * @copyright
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @section DESCRIPTION
 * */

#include "agent-framework/module/common_components.hpp"
#include "agent-framework/module/compute_components.hpp"
#include "agent-framework/command/registry.hpp"
#include "agent-framework/command/compute_commands.hpp"

using namespace agent_framework::command;
using namespace agent_framework::module;
using namespace agent_framework::model;

namespace {
    void process_collections(Manager& manager) {
        if (CommonComponents::get_instance()->
                get_system_manager().get_entry_count(manager.get_uuid()) > 0) {
            manager.add_collection(attribute::Collection(enums::CollectionName::Systems,
                    enums::CollectionType::Systems, ""));
        }
        if (CommonComponents::get_instance()->
                get_module_manager().get_entry_count(manager.get_uuid()) > 0) {
            manager.add_collection(attribute::Collection(enums::CollectionName::Managers,
                    enums::CollectionType::Managers,""));
        }
        if (CommonComponents::get_instance()->
                get_chassis_manager().get_entry_count(manager.get_uuid()) > 0) {
            manager.add_collection(attribute::Collection(enums::CollectionName::Chassis,
                        enums::CollectionType::Chassis,""));
        }
    }
}

REGISTER_COMMAND(GetManagerInfo,
    [] (const GetManagerInfo::Request& req, GetManagerInfo::Response& rsp) {
        log_debug("agent", "Getting manager info.");
        rsp = CommonComponents::get_instance()->
            get_module_manager().get_entry(req.get_uuid());
        process_collections(rsp);
    }
);
