// -*- compile-command: "g++ -std=c++17 extract.cpp -o extract"; -*-
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <vector>

// [BEGIN_Item_Test]
// Generate a org mode link:
// #+BEGIN_EXAMPLE
// hfile:path/file.cpp::line
// #+END_EXAMPLE
//
static inline std::string
org_file_link(const std::string& filename, const std::size_t line)
{
  return "file:" + filename + "::" + std::to_string(line);
}

// [BEGIN_Item]
// [DOC]
// A structure to store extracted data
class Item
{
  // [END_Item]

  std::string _filename;

  // [DOC]
  // An enum
  enum Category_Enum
  {
    Comment,
    Code,
    Undefined
  };
  using doc_element_type = std::pair<Category_Enum, std::string>;
  std::vector<doc_element_type> _doc;

 protected:
  void insert_mark(const std::size_t line)
  {
    _doc.push_back(doc_element_type(Comment, "# " + org_file_link(_filename, line)));
  }

 public:
  // [BEGIN_Item]
  // *Public Constructors*
  //
  // - =filename=: filename to process
  //
  Item(const std::string filename)
      // [END_Item]
      : _filename(filename)
  {
  }
  // [END_Item_Test]

  void insert_comment(const std::size_t line, const std::string& comment)
  {
    if (_doc.empty() or _doc.back().first == Code) insert_mark(line);

    _doc.push_back(doc_element_type(Comment, comment));
  }

  void insert_code(const std::size_t line, const std::string& code)
  {
    if (_doc.empty()) insert_mark(line);

    _doc.push_back(doc_element_type(Code, code));
  }

  friend std::ostream& operator<<(std::ostream& out, const Item& to_print)
  {
    const char src_begin[] = "#+BEGIN_SRC cpp -r -l \"// (ref:%s)\" :eval never";
    const char src_end[]   = "#+END_SRC";

    if (to_print._doc.empty())
    {
      return out;
    }

    out << "#+BEGIN_QUOTE" << std::endl;
    Category_Enum state = Undefined;

    for (const auto category_line : to_print._doc)
    {
      switch (state)
      {
        case Undefined:
        {
          if (category_line.first == Code)
          {
            out << src_begin << std::endl;
            out << category_line.second << std::endl;
          }
          else
          {
            // For the moment only 2 categories
            assert(category_line.first == Comment);

            out << category_line.second << std::endl;
          }
          state = category_line.first;
          continue;
        }
        case Code:
        {
          if (category_line.first == Code)
          {
            out << category_line.second << std::endl;
          }
          else
          {
            // For the moment only 2 categories
            assert(category_line.first == Comment);

            out << src_end << std::endl;
            //
            out << category_line.second << std::endl;
          }
          state = category_line.first;
          continue;
        }
        case Comment:
        {
          if (category_line.first == Code)
          {
            out << src_begin << std::endl;
            out << category_line.second << std::endl;
          }
          else
          {
            // For the moment only 2 categories
            assert(category_line.first == Comment);

            out << category_line.second << std::endl;
          }
          state = category_line.first;
          continue;
        }
      }
    }

    if (state == Code)
    {
      out << src_end << std::endl;
    }
    out << "#+END_QUOTE" << std::endl;

    return out;
  }
};
//  [END_Item]

class Tag_Stack
{
 public:
  using stack_element_type = std::pair<std::size_t, std::string>;

 private:
  std::string _filename;
  std::vector<std::string> _error_msg;
  std::map<std::string, std::size_t> _tags;  // [tag]=line

 public:
  Tag_Stack(const std::string& filename) : _filename(filename) {}
  bool tag_begin(const std::size_t line, const std::string& tag)
  {
    bool ok = true;

    //+ check if this peculiar tag alread exist
    //
    if (_tags.count(tag) > 0)
    {
      ok = false;
      _error_msg.push_back("# ERROR: tag " + tag + ", here " + org_file_link(_filename, line) +
                           "\n"
                           "#     |  already opened here: " +
                           org_file_link(_filename, _tags[tag]));
    }
    else
    {
      _tags[tag] = line;
    }
    return ok;
  }

  // +
  // Prints an error message in this situation:
  // #+begin_example
  // // [BEGIN_TAG_1]
  // // ...
  // // [BEGIN_TAG_A]
  // // ...
  // // [END_TAG_1]
  // // ...
  // // [END_TAG_A]
  // #+end_example
  // we cannot check that the tag we close is the last opened tag
  //
  bool tag_end(const std::size_t line, const std::string& tag)
  {
    bool ok = true;
    if (_tags.count(tag) == 0)
    {
      ok = false;
      _error_msg.push_back("# ERROR: tag is not opened but ended here: " +
                           org_file_link(_filename, line));
    }
    else
    {
      _tags.erase(tag);
    }
    return ok;
  }

  bool is_ok() const { return _error_msg.empty() and _tags.empty(); }

  friend std::ostream& operator<<(std::ostream& out, const Tag_Stack& to_print)
  {
    if (to_print.is_ok())
    {
      out << "# no error :-)" << std::endl;
    }
    else
    {
      for (const auto& error_msg_i : to_print._error_msg)
      {
        out << error_msg_i << std::endl;
      }
      if (not to_print._tags.empty())
      {
        out << "# ERROR: list of opened but not closed tags:" << std::endl;
        for (const auto& [tag, line] : to_print._tags)
        {
          out << "#     | tag " << tag << ", here:" << org_file_link(to_print._filename, line)
              << std::endl;
        }
      }
    }
    return out;
  }
};

// [BEGIN_Item_All]
std::pair<Item, Tag_Stack>
parse(const std::string& filename, const std::string& tag)
{
  std::regex regex_tag_begin("^[ \t]*// \\[BEGIN_([_[:alnum:]]+)\\][ \t]*$");
  std::regex regex_tag_end("^[ \t]*// \\[END_([_[:alnum:]]+)\\][ \t]*$");
  std::regex regex_tag_doc("^[ \t]*// \\[DOC\\][ \t]*$");
  std::regex regex_comment("^[ \t]*//(.*)$");

  // We ignore isolated link
  //
  // [[id:9acbd7a5-bad9-4f19-b9fe-58b20d26dedf][[Finding the calibration]]
  //
  // as they are user link to retrieve org section from source
  //
  std::regex tag_isolated_link(
      "^[ \t]*//[ \t]*\\[\\[[^\\[^\\]]*\\]\\[[^\\[^\\]]*\\]\\]$");  // [[...][...]] org link

  enum state_enum
  {
    skip,            // BEGIN_tag not found yet
    tagged_comment,  // begin of tagged block (with the right tag)
    tagged_code,     // code block between tagged_comment and tag_end
  };

  std::fstream file(filename.c_str());
  // std::vector<Item> buffer;
  Item item(filename);
  state_enum state = skip;
  std::string line;
  std::size_t line_count = 0;
  Tag_Stack tag_stack(filename);  // its main role is to analyse nested begin/end
                                  // to print error message

  while (std::getline(file, line))
  {
    ++line_count;

    switch (state)
    {
      case skip:
      {
        if (std::regex_match(line, regex_comment))
        {
          // if (std::regex_match(line, tag_isolated_link))
          // {
          //   continue;
          // }

          // if (std::regex_match(line, regex_tag_doc))
          // {
          //   // Just found a [DOC] !
          //   //
          //   //  state = tagged_comment;
          //   continue;
          // }

          if (std::regex_match(line, regex_tag_begin))
          {
            // Just found a [BEGIN_XXX] !
            //
            std::smatch extracted_match;
            std::regex_match(line, extracted_match, regex_tag_begin);
            tag_stack.tag_begin(line_count, extracted_match[1]);

            if (extracted_match[1] == tag)
            {
              // This is our [BEGIN_Tag] !
              //
              state = tagged_comment;
            }
            continue;
          }

          if (std::regex_match(line, regex_tag_end))
          {
            // Just found a [END_XXX] !
            //
            std::smatch extracted_match;
            std::regex_match(line, extracted_match, regex_tag_end);
            tag_stack.tag_end(line_count, extracted_match[1]);
            continue;
          }
        }
        continue;
      }

      case tagged_comment:
      {
        if (std::regex_match(line, regex_comment))
        {
          if (std::regex_match(line, tag_isolated_link))
          {
            continue;
          }

          if (std::regex_match(line, regex_tag_doc))
          {
            continue;
          }

          if (std::regex_match(line, regex_tag_begin))
          {
            // Just found a [BEGIN_XXX] !
            //
            std::smatch extracted_match;
            std::regex_match(line, extracted_match, regex_tag_begin);
            tag_stack.tag_begin(line_count, extracted_match[1]);
            continue;
          }
          if (std::regex_match(line, regex_tag_end))
          {
            // Just found a [END_XXX] !
            //
            std::smatch extracted_match;
            std::regex_match(line, extracted_match, regex_tag_end);
            tag_stack.tag_end(line_count, extracted_match[1]);

            if (extracted_match[1] == tag)
            {
              // This is our [END_Tag] !
              //
              state = skip;
            }
            continue;
          }

          // "regular" tagged comment
          //
          std::smatch extracted_match;
          std::regex_match(line, extracted_match, regex_comment);
          item.insert_comment(line_count, extracted_match[1]);
          continue;
        }

        // No more comment, switch back to tagged code
        //
        item.insert_code(line_count, line);
        state = tagged_code;
        continue;
      }

      case tagged_code:
      {
        if (std::regex_match(line, tag_isolated_link))
        {
          continue;
        }

        if (std::regex_match(line, regex_tag_doc))
        {
          state = tagged_comment;
          continue;
        }

        if (std::regex_match(line, regex_tag_begin))
        {
          // Just found a new tag [BEGIN_XXX]
          std::smatch extracted_match;
          std::regex_match(line, extracted_match, regex_tag_begin);
          assert(extracted_match.size() == 2);  // 0=whole line, 1=extracted tag
          tag_stack.tag_begin(line_count, extracted_match[1]);
          continue;
        }

        if (std::regex_match(line, regex_tag_end))
        {
          std::smatch extracted_match;
          std::regex_match(line, extracted_match, regex_tag_end);
          assert(extracted_match.size() == 2);
          tag_stack.tag_end(line_count, extracted_match[1]);

          if (extracted_match[1] == tag)  // right tag!
          {
            state = skip;
            continue;
          }
          continue;  // ignore [END_XXX] (nested tag support)
        }

        item.insert_code(line_count, line);  // regular code
        continue;
      }

      default:
        assert(0);
        exit(-1);
    }
  }
  return std::make_pair(item, tag_stack);
}
// [END_Item_All]

std::ostream&
operator<<(std::ostream& out, std::vector<Item>& to_print)
{
  for (const auto& item : to_print)
  {
    out << item;
  }
  return out;
}

int
main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cout << "\n" << argv[0] << " [cpp file] [tag]";
    exit(EXIT_FAILURE);
  }

  auto [item, tag_stack] = parse(argv[1], argv[2]);
  std::cout << tag_stack;
  std::cout << item << std::endl;
  return EXIT_SUCCESS;
}
