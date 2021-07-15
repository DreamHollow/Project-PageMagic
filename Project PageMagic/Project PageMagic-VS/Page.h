/// Everything is handled by the Page class now.
#ifndef PAGE_H
#define PAGE_H

#include "pch.h"

extern std::string full_file;

class Page
{
public:
	Page();
	virtual ~Page();

	// Templates
	// template <typename T, std::size_t N> T* end_(T(&arr)[N]) { return arr + N; };
	
	// Variables
	std::string decision;
	int global_line = 0;
	int* global_point = nullptr;

	// Methods
	inline std::string const get_title() { return title_header; };
	bool create_file();
	// void open_file();
	void setup();
	void memory_cleaner();

private:
	// Variables
	// Tagger is initialized in constructor.
	int tagger;
	int* tag_pointer = nullptr;

	int temp;
	int* t_point = nullptr;

	// This tag is used all over the Page class for in-code debugging purposes. Switch to FALSE if you're not debugging.
	bool page_debug;
	bool standard_tag = true;

	char file_search[500];
	char option;
	std::string filetype{ ".html" };
	std::string f_name;
	char title_header[100] = "Untitled"; // Default title for created pages.
	std::vector<std::string> html_tags; // All beginning tags are here.
	std::vector<std::string> html_end;
	std::string tag_grab;

	// Tagging Variables
	char tag_filler[500]; // Stored in the stack
	// std::string local_string;
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
	void initialize_tags();
	inline int const find_line() { return *global_point; };
	std::string s_state(int num);
	void declare(std::string local_file);
	void title_sequence();
	void display_all();
	void page_setup();
	void page_explain();
	void tag_begin();
	void editing_process();
	void meta_process();
	void hyperlink_process();
	std::string tag_fill();
};

#endif