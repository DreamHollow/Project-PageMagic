/// Everything is handled by the Page class now.
#ifndef PAGE_H
#define PAGE_H

#include "Manager.hpp"
#include <vector>

/* Most functions have an int return type to be passed down to the error functions to determine where things went wrong.
Very serious errors return "2" and are usually memory related. */

class Page
{
public:
	Page();
	virtual ~Page();

	Manager manager;

	// Accessors
	const bool is_debugging() const { return page_debug; };
	
	// Variables
	std::string decision;
	int global_line = 0;
	bool is_running = false;
	int err_code{};
	int &err_ref = err_code;

	// Methods
	inline std::string const get_title() { return title_header; };
	int start_file();
	bool error_detected(int &err_ref);
	int page_setup();

private:
	// Pointers / Memory Objects
	// std::unique_ptr<Page> MyPage; // Not sure if this is needed here...
	int* global_point = nullptr;
	int* tag_pointer = nullptr;
	int* t_point = nullptr;

	// Variables
	int tagger;
	int temp;

	// Assign Once Only
	int &global_ref = global_line;
	int &t_ref = temp;
	int &global_err = err_code;

	// Booleans
	bool warning_displayed = false; // Used to prevent the program from using the error warning multiple times
	bool page_debug; // This tag is used all over the Page class for in-code debugging purposes. Switch to FALSE if you're not debugging.
	bool standard_tag = true;
	bool ignore_tag = false;
	bool main_tag = false;
	bool sub_tag = false;

	/* Sub-tagging system will detect and prevent tags from being used if they cannot exist in <body> or <head> without formatting. */

	// Strings
	std::string option{};
	std::string title_header = "Untitled"; // Default title for created pages.
	std::vector<std::string> html_tags;
	std::vector<std::string> html_end;
	std::string tag_grab;

	// Variable tagging went through EXTENSIVE rewriting and char arrays will no longer be used. The string system should be safe enough for this.

	// Tagging Variables
	std::string tag_filler; // Holds the actual strings applied to each tag -- NOT to be confused with the tags themselves
	std::string complete_string;

	// Tagging Hyperlinks etc.
	std::string local_hyperlink;
	std::string complete_hyperlink;
	std::string link_end = "'>"; // Needs to exist to close off the link properly - Needs to change for tagging system to work properly

	// Sub-tagging Variables
	std::string sub_hyperlink;
	std::string sub_complete;

	// It was a nightmare trying to figure out what C++11's implementation of this system is. Used default.
	enum WEBTAGS
	{
		COMMENT = 0, HYPERLINK, ABBREVIATE, ADDRESS, AREA, ARTICLE, ASIDE, AUDIO,
		BDI, BDO, BLOCKQUOTE, BODY, BREAK, BUTTON, CANVAS, CAPTION, CITE, CODE,
		COLUMN, COLUMNGROUP, DATA, DATALIST, DESCRIPTLIST, DELETED, DETAILS,
		DEFINED, DIALOG, DIV, DESCLIST, DESCTERM, EMPHASIZE, EMBED, FIELDSET,
		FIGCAPTION, FIGURE, FOOTER, FORM, H1, H2, H3, H4, H5, H6, HEAD, HEADER,
		HORZRULER, HTMLROOT, ITALICS, IFRAME, IMG, INPUT, INS, KEYBOARD,
		LABEL, LEGEND, LISTITEM, LINK, MAIN, IMGMAP, MARK, META, METER,
		NAV, NOSCRIPT, OBJECT, ORDERLIST, OPTGROUP, OPTION, OUTPUT, PARAGRAPH,
		PARAMETER, PICTURE, PREFORMAT, PROGRESS, SHORTQUOTE, NORUBY,
		STRIKEOUT, SAMPLE, SCRIPT, SECTION, SELECT, SMALL, SOURCE, SPAN,
		STRONGTEXT, STYLE, SUBSCRIPT, SUMMARY, SUPERSCRIPT, SVG,
		TABLE, TBODY, TABLECELL, TEMPLATE, TEXTAREA, TABLEFOOT,
		TABLEHEAD, THEADCONT, TIME, TITLE, TABLEROW, TRACK, UNORDERLIST,
		VARIABLE, VIDEO, WEBLINEBREAK, XEND
	};

	// Methods
	void init_settings();
	void const show_error();
	void init_tags();
	void err_set(int error_type) { this->err_code = error_type; };
	inline int const find_line() { return *global_point; };
	std::string const s_state(int num) const { return this->html_tags.at(num); };
	void title_sequence();
	int display_all();
	void const page_explain();
	int maintag_begin();
	int subtag_begin();
	int editing_process();
	int meta_process();
	int hyperlink_process();
	std::string const tag_fill() { return this->tag_filler; };
	void data_cleaner();
	int tagging_loop();
	int tag_finish();
	const void tag_warning();
};

#endif