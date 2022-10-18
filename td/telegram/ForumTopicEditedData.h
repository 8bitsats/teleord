//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2022
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "td/telegram/CustomEmojiId.h"
#include "td/telegram/td_api.h"

#include "td/utils/common.h"
#include "td/utils/StringBuilder.h"

namespace td {

class ForumTopicEditedData {
  string title_;
  CustomEmojiId icon_custom_emoji_id_;
  bool edit_icon_custom_emoji_id_ = false;
  bool edit_is_closed_ = false;
  bool is_closed_ = false;

  friend StringBuilder &operator<<(StringBuilder &string_builder, const ForumTopicEditedData &topic_edited_data);

 public:
  ForumTopicEditedData() = default;

  bool is_empty() const {
    return title_.empty() && !edit_icon_custom_emoji_id_ && !edit_is_closed_;
  }

  ForumTopicEditedData(string &&title, bool edit_icon_custom_emoji_id, int64 icon_custom_emoji_id, bool edit_is_closed,
                       bool is_closed)
      : title_(std::move(title))
      , icon_custom_emoji_id_(icon_custom_emoji_id)
      , edit_icon_custom_emoji_id_(edit_icon_custom_emoji_id)
      , edit_is_closed_(edit_is_closed)
      , is_closed_(is_closed) {
  }

  td_api::object_ptr<td_api::forumTopicEditedData> get_forum_topic_edited_data_object() const;
};

StringBuilder &operator<<(StringBuilder &string_builder, const ForumTopicEditedData &topic_edited_data);

}  // namespace td
