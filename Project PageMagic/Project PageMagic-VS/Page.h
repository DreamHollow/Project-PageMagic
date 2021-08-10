/// Everything is handled by the Page class now.
#ifndef PAGE_H
#define PAGE_H

#include "pch.h"
#include <string> // Including this seperate because it doesn't play nice with PCH

// I do not recommend doing this often, but in this case I was using full_file as a global.
extern std::string full_file;

class Page
{
public:
	Page();
	virtual ~Page();
	
	// Variables
	std::string decision;
	int global_line = 0;
	bool is_running = false;
	int err_code = 0; // Should be 0 by default to interpret non-error

	// Methods
	inline std::string const get_title() { return title_header; };
	bool create_file();
	void setup();

private:
	// Pointers / Memory Objects
	std::unique_ptr<Page> MyPage;
	int* global_point = nullptr;
	int* tag_pointer = nullptr;
	int* t_point = nullptr;

	// Variables
	int tagger;
	int temp;

	// Assign Once Only
	int &global_ref = global_line;
	int &t_ref = temp;

	// This tag is used all over the Page class for in-code debugging purposes. Switch to FALSE if you're not debugging.
	bool page_debug;
	bool standard_tag = true;
	bool ignore_tag = false;

	char option; // This is the only non-string input
	std::string filetype{ ".html" };
	std::string f_name;
	std::string title_header = "Untitled"; // Default title for created pages.
	std::vector<std::string> html_tags; // All beginning tags are here.
	std::vector<std::string> html_end;
	std::string tag_grab;

	// Variable tagging went through EXTENSIVE rewriting and char arrays will no longer be used. The string system should be safe enough for this.

	// Tagging Variables
	std::string tag_filler;
	std::string complete_string;

	// Tagging Hyperlinks etc.
	std::string local_hyperlink;
	std::string complete_hyperlink;
	std::string link_end = "'>"; // Needs to exist to close off the link properly.

	// It was a nightmare trying to figure out what C++11's implementation of this system is.
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
	// bool valid_ref(int &ref_address);
	void initialize_tags();
	inline int const find_line() { return *global_point; };
	std::string s_state(int num);
	void declare(std::string local_file);
	void title_sequence();
	int display_all();
	int page_setup();
	void page_explain();
	int tag_begin();
	void editing_process();
	void meta_process();
	void hyperlink_process();
	std::string tag_fill();
	void memory_cleaner();
};

#endif