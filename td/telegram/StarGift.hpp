//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2024
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "td/telegram/Global.h"
#include "td/telegram/StarGift.h"
#include "td/telegram/StickersManager.h"
#include "td/telegram/StickersManager.hpp"
#include "td/telegram/Td.h"

#include "td/utils/common.h"
#include "td/utils/tl_helpers.h"

namespace td {

template <class StorerT>
void StarGift::store(StorerT &storer) const {
  CHECK(is_valid());
  Td *td = storer.context()->td().get_actor_unsafe();
  bool is_limited = availability_total_ != 0;
  BEGIN_STORE_FLAGS();
  STORE_FLAG(is_limited);
  END_STORE_FLAGS();
  td::store(id_, storer);
  td->stickers_manager_->store_sticker(sticker_file_id_, false, storer, "StarGift");
  td::store(star_count_, storer);
  if (is_limited) {
    td::store(availability_remains_, storer);
    td::store(availability_total_, storer);
  }
}

template <class ParserT>
void StarGift::parse(ParserT &parser) {
  Td *td = parser.context()->td().get_actor_unsafe();
  bool is_limited;
  BEGIN_PARSE_FLAGS();
  PARSE_FLAG(is_limited);
  END_PARSE_FLAGS();
  td::parse(id_, parser);
  sticker_file_id_ = td->stickers_manager_->parse_sticker(false, parser);
  td::parse(star_count_, parser);
  if (is_limited) {
    td::parse(availability_remains_, parser);
    td::parse(availability_total_, parser);
  }
}

}  // namespace td
