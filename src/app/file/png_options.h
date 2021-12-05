// Aseprite
// Copyright (C) 2019  Igara Studio S.A.
//
// This program is distributed under the terms of
// the End-User License Agreement for Aseprite.

#ifndef APP_FILE_PNG_OPTIONS_H_INCLUDED
#define APP_FILE_PNG_OPTIONS_H_INCLUDED
#pragma once

#include "app/file/format_options.h"
#include "base/buffer.h"
#include "png.h"

namespace app {

  // Data for PNG files
  class PngOptions : public FormatOptions {
  public:
    PngOptions() : keepTextChunks(true) { }
    struct Chunk {
      std::string name;
      base::buffer data;
      // Flags PNG_HAVE_IHDR/PNG_HAVE_PLTE/PNG_AFTER_IDAT
      int location;
    };

    struct TextStore {
      int  compression;

      std::string key;
      std::string text;

      size_t text_length;
      size_t itxt_length;

      std::string lang;
      std::string lang_key;
    };

    using Texts = std::vector<TextStore>;

    using Chunks = std::vector<Chunk>;

    void addtxt(TextStore&& txt) {
      m_userTexts.emplace_back(std::move(txt));
    }

    void clear_txt() { 
      m_userTexts.clear();
    }

    int txtsize() const {
      return int(m_userTexts.size());
    }

    void addChunk(Chunk&& chunk) {
      m_userChunks.emplace_back(std::move(chunk));
    }

    bool isEmpty() const {
      if(m_userChunks.empty() && m_userTexts.empty()) {
        return true;
      }
      else {
        return false;
      }
    }

    int size() const {
      return int(m_userChunks.size());
    }

    const Chunks& chunks() const { return m_userChunks; }

    const Texts& texts() const { return m_userTexts; }

    bool keepTextChunks;
  private:
    Chunks m_userChunks;
    Texts m_userTexts;
  };

} // namespace app

#endif
