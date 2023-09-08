//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2023
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "td/telegram/AccountManager.h"

namespace td {

AccountManager::AccountManager(Td *td, ActorShared<> parent) : td_(td), parent_(std::move(parent)) {
}

void AccountManager::tear_down() {
  parent_.reset();
}

void AccountManager::get_current_state(vector<td_api::object_ptr<td_api::Update>> &updates) const {
}

}  // namespace td
