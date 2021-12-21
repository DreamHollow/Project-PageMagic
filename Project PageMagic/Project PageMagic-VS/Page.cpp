#include "Page.hpp"

/* err_code is a general purpose variable. If it ever returns anything except 0, something went wrong.
* The functions that return ints are intended to catch exceptions and force Page object to return to main.
* The file access system is a work in progress. */

Page::Page()
{
	this->init_settings();
	this->init_tags();
};

Page::~Page()
{
	if (debugbot.is_debugging() == true)
	{
		std::cout << std::endl;
		std::cout << "Deconstructor was called; left the scope of Page object." << std::endl;
		std::cout << std::endl;
	}

	// Just empties strings and other pre-set information.
	this->data_cleaner();
};

void Page::init_settings()
{
	this->temp = 0;
	this->t_point = &temp;

	this->global_line = 1;
	this->global_point = &global_line; // Do NOT try to delete these kinds of pointers. Learned the hard way.

	this->tagger = 0; // The actual tagging variable being used.
	this->tag_pointer = &tagger; // The tag pointer used to determine which tag is edited.

	this->option = 'a'; // Initialized to junk, is set during function.
};

// This is const because it should only ever show error messages and only ONCE
void const Page::show_error()
{
	std::cout << "There was an error during execution." << std::endl;
	std::cout << "[Error Code: ";

	switch (this->err_code)
	{
	case 1:
		std::cout << "1, Standard Error]" << std::endl;
		break;
	case 2:
		std::cout << "2, Elevated Error - Please report this to the developer]" << std::endl;
		break;
	default:
		std::cout << "Unknown error!]" << std::endl;
		break;
	}
}

// Tags initialized here are called upon using a corresponding enum
void Page::init_tags()
{
	// There are an absolutely MASSIVE amount of HTML tags. I didn't even know some of these existed.
	// Enum will keep track of which tags to deploy, vector will fill the tags.
	this->html_tags.push_back("<!--"); // 0; Very different from most tags
	this->html_tags.push_back("<a>"); // 1; Must be modified to contain a value like a URL
	this->html_tags.push_back("<abbr>"); // 2
	this->html_tags.push_back("<address>"); // 3
	this->html_tags.push_back("<area>"); // 4
	this->html_tags.push_back("<article>"); // 5
	this->html_tags.push_back("<aside>"); // 6
	this->html_tags.push_back("<audio>"); // 7; Must be modified
	this->html_tags.push_back("<bdi>"); // 8
	this->html_tags.push_back("<bdo>"); // 9
	this->html_tags.push_back("<blockquote>"); // 10
	this->html_tags.push_back("<body>"); // 11; this tag should really be included before ALL content.
	this->html_tags.push_back("<br>"); // 12; line break
	this->html_tags.push_back("<button>"); // 13
	this->html_tags.push_back("<canvas>"); // 14
	this->html_tags.push_back("<caption>"); // 15; accessibility options
	this->html_tags.push_back("<cite>"); // 16
	this->html_tags.push_back("<code>"); // 17; very important to programmers
	this->html_tags.push_back("<col>"); // 18
	this->html_tags.push_back("<colgroup>"); // 19; contains a group of columns
	this->html_tags.push_back("<data>"); // 20; allows machine readable code
	this->html_tags.push_back("<datalist>"); // 21
	this->html_tags.push_back("<dd>"); // 22
	this->html_tags.push_back("<del>"); // 23
	this->html_tags.push_back("<details>"); // 24
	this->html_tags.push_back("<dfn>"); // 25
	this->html_tags.push_back("<dialog>"); // 26
	this->html_tags.push_back("<div>"); // 27
	this->html_tags.push_back("<dl>"); // 28
	this->html_tags.push_back("<dt>"); // 29
	this->html_tags.push_back("<em>"); // 30
	this->html_tags.push_back("<embed>"); // 31
	this->html_tags.push_back("<fieldset>"); // 32
	this->html_tags.push_back("<figcaption>"); // 33
	this->html_tags.push_back("<figure>"); // 34
	this->html_tags.push_back("<footer>"); // 35
	this->html_tags.push_back("<form>"); // 36
	this->html_tags.push_back("<h1>"); // 37
	this->html_tags.push_back("<h2>"); // 38
	this->html_tags.push_back("<h3>"); // 39
	this->html_tags.push_back("<h4>"); // 40
	this->html_tags.push_back("<h5>"); // 41
	this->html_tags.push_back("<h6>"); // 42
	this->html_tags.push_back("<head>"); // 43
	this->html_tags.push_back("<header>"); // 44
	this->html_tags.push_back("<hr>"); // 45
	this->html_tags.push_back("<html>"); // 46; INVALID - ROOT
	this->html_tags.push_back("<i>"); // 47
	this->html_tags.push_back("<iframe>"); // 48
	this->html_tags.push_back("<img>"); // 49; requires modification
	this->html_tags.push_back("<input>"); // 50
	this->html_tags.push_back("<ins>"); // 51
	this->html_tags.push_back("<kbd>"); // 52
	this->html_tags.push_back("<label>"); // 53
	this->html_tags.push_back("<legend>"); // 54
	this->html_tags.push_back("<li>"); // 55
	this->html_tags.push_back("<link>"); // 56
	this->html_tags.push_back("<main>"); // 57
	this->html_tags.push_back("<map>"); // 58
	this->html_tags.push_back("<mark>"); // 59
	this->html_tags.push_back("<meta>"); // 60
	this->html_tags.push_back("<meter>"); // 61
	this->html_tags.push_back("<nav>"); // 62
	this->html_tags.push_back("<noscript>"); // 63
	this->html_tags.push_back("<object>"); // 64
	this->html_tags.push_back("<ol>"); // 65
	this->html_tags.push_back("<optgroup"); // 66
	this->html_tags.push_back("<option>"); // 67
	this->html_tags.push_back("<output>"); // 68
	this->html_tags.push_back("<p>"); // 69
	this->html_tags.push_back("<param>"); // 70
	this->html_tags.push_back("<picture>"); // 71
	this->html_tags.push_back("<pre>"); // 72
	this->html_tags.push_back("<progress>"); // 73
	this->html_tags.push_back("<q>"); // 74
	this->html_tags.push_back("<rp>"); // 75; "no ruby"
	this->html_tags.push_back("<s>"); // 76
	this->html_tags.push_back("<samp>"); // 77
	this->html_tags.push_back("<script>"); // 78
	this->html_tags.push_back("<section>"); // 79
	this->html_tags.push_back("<select>"); // 80
	this->html_tags.push_back("<small>"); // 81
	this->html_tags.push_back("<source>"); // 82
	this->html_tags.push_back("<span>"); // 83
	this->html_tags.push_back("<strong>"); // 84
	this->html_tags.push_back("<style>"); // 85
	this->html_tags.push_back("<sub>"); // 86
	this->html_tags.push_back("<summary>"); // 87
	this->html_tags.push_back("<sup>"); // 88
	this->html_tags.push_back("<svg>"); // 89
	this->html_tags.push_back("<table>"); // 90
	this->html_tags.push_back("<tbody>"); // 91
	this->html_tags.push_back("<td>"); // 92
	this->html_tags.push_back("<template>"); // 93
	this->html_tags.push_back("<textarea>"); // 94
	this->html_tags.push_back("<tfoot>"); // 95
	this->html_tags.push_back("<th>"); // 96
	this->html_tags.push_back("<thead>"); // 97
	this->html_tags.push_back("<time>"); // 98
	this->html_tags.push_back("<title>"); // 99; INVALID
	this->html_tags.push_back("<tr>"); // 100
	this->html_tags.push_back("<track>"); // 101
	this->html_tags.push_back("<ul>"); // 102
	this->html_tags.push_back("<var>"); // 103
	this->html_tags.push_back("<video>"); // 104
	this->html_tags.push_back("<wbr>"); // 105
	this->html_tags.push_back("NULL"); // 106, used for invalid tags



	// Matching all of the opening tags to the closing tags.
	this->html_end.push_back("-->"); // 0
	this->html_end.push_back("</a>"); // 1; Must be modified to contain a value like a URL
	this->html_end.push_back("</abbr>"); // 2
	this->html_end.push_back("</address>"); // 3
	this->html_end.push_back("</area>"); // 4
	this->html_end.push_back("</article>"); // 5
	this->html_end.push_back("</aside>"); // 6
	this->html_end.push_back("</audio>"); // 7; Must be modified
	this->html_end.push_back("</bdi>"); // 8
	this->html_end.push_back("</bdo>"); // 9
	this->html_end.push_back("</blockquote>"); // 10
	this->html_end.push_back("</body>"); // 11; this tag should really be included before ALL content.
	this->html_end.push_back("</br>"); // 12; line break
	this->html_end.push_back("</button>"); // 13
	this->html_end.push_back("</canvas>"); // 14
	this->html_end.push_back("</caption>"); // 15; accessibility options
	this->html_end.push_back("</cite>"); // 16
	this->html_end.push_back("</code>"); // 17; very important to programmers
	this->html_end.push_back("</col>"); // 18
	this->html_end.push_back("</colgroup>"); // 19; contains a group of columns
	this->html_end.push_back("</data>"); // 20; allows machine readable code
	this->html_end.push_back("</datalist>"); // 21
	this->html_end.push_back("</dd>"); // 22
	this->html_end.push_back("</del>"); // 23
	this->html_end.push_back("</details>"); // 24
	this->html_end.push_back("</dfn>"); // 25
	this->html_end.push_back("</dialog>"); // 26
	this->html_end.push_back("</div>"); // 27
	this->html_end.push_back("</dl>"); // 28
	this->html_end.push_back("</dt>"); // 29
	this->html_end.push_back("</em>"); // 30
	this->html_end.push_back("</embed>"); // 31
	this->html_end.push_back("</fieldset>"); // 32
	this->html_end.push_back("</figcaption>"); // 33
	this->html_end.push_back("</figure>"); // 34
	this->html_end.push_back("</footer>"); // 35
	this->html_end.push_back("</form>"); // 36
	this->html_end.push_back("</h1>"); // 37
	this->html_end.push_back("</h2>"); // 38
	this->html_end.push_back("</h3>"); // 39
	this->html_end.push_back("</h4>"); // 40
	this->html_end.push_back("</h5>"); // 41
	this->html_end.push_back("</h6>"); // 42
	this->html_end.push_back("</head>"); // 43
	this->html_end.push_back("</header>"); // 44
	this->html_end.push_back("</hr>"); // 45
	this->html_end.push_back("</html>"); // 46; INVALID - ROOT
	this->html_end.push_back("</i>"); // 47
	this->html_end.push_back("</iframe>"); // 48
	this->html_end.push_back("</img>"); // 49; requires modification
	this->html_end.push_back("</input>"); // 50
	this->html_end.push_back("</ins>"); // 51
	this->html_end.push_back("</kbd>"); // 52
	this->html_end.push_back("</label>"); // 53
	this->html_end.push_back("</legend>"); // 54
	this->html_end.push_back("</li>"); // 55
	this->html_end.push_back("</link>"); // 56
	this->html_end.push_back("</main>"); // 57
	this->html_end.push_back("</map>"); // 58
	this->html_end.push_back("</mark>"); // 59
	this->html_end.push_back("</meta>"); // 60
	this->html_end.push_back("</meter>"); // 61
	this->html_end.push_back("</nav>"); // 62
	this->html_end.push_back("</noscript>"); // 63
	this->html_end.push_back("</object>"); // 64
	this->html_end.push_back("</ol>"); // 65
	this->html_end.push_back("</optgroup"); // 66
	this->html_end.push_back("</option>"); // 67
	this->html_end.push_back("</output>"); // 68
	this->html_end.push_back("</p>"); // 69
	this->html_end.push_back("</param>"); // 70
	this->html_end.push_back("</picture>"); // 71
	this->html_end.push_back("</pre>"); // 72
	this->html_end.push_back("</progress>"); // 73
	this->html_end.push_back("</q>"); // 74
	this->html_end.push_back("</rp>"); // 75; "no ruby"
	this->html_end.push_back("</s>"); // 76
	this->html_end.push_back("</samp>"); // 77
	this->html_end.push_back("</script>"); // 78
	this->html_end.push_back("</section>"); // 79
	this->html_end.push_back("</select>"); // 80
	this->html_end.push_back("</small>"); // 81
	this->html_end.push_back("</source>"); // 82
	this->html_end.push_back("</span>"); // 83
	this->html_end.push_back("</strong>"); // 84
	this->html_end.push_back("</style>"); // 85
	this->html_end.push_back("</sub>"); // 86
	this->html_end.push_back("</summary>"); // 87
	this->html_end.push_back("</sup>"); // 88
	this->html_end.push_back("</svg>"); // 89
	this->html_end.push_back("</table>"); // 90
	this->html_end.push_back("</tbody>"); // 91
	this->html_end.push_back("</td>"); // 92
	this->html_end.push_back("</template>"); // 93
	this->html_end.push_back("</textarea>"); // 94
	this->html_end.push_back("</tfoot>"); // 95
	this->html_end.push_back("</th>"); // 96
	this->html_end.push_back("</thead>"); // 97
	this->html_end.push_back("</time>"); // 98
	this->html_end.push_back("</title>"); // 99; INVALID
	this->html_end.push_back("</tr>"); // 100
	this->html_end.push_back("</track>"); // 101
	this->html_end.push_back("</ul>"); // 102
	this->html_end.push_back("</var>"); // 103
	this->html_end.push_back("</video>"); // 104
	this->html_end.push_back("</wbr>"); // 105
	this->html_end.push_back("NULL"); // 106
};

// This can't be const because it does modify some data
int Page::display_all()
{
	if (this->t_point == nullptr || t_point == NULL) // The function should end abruptly if the pointers malfunction
	{
		std::cout << "Error, no memory could be allocated to this pointer!";
		std::cout << "The tag display function encountered some problems and must be terminated." << std::endl;
		std::cout << std::endl;

		// Don't delete the pointer, just return an error. Deleting raw pointers is bad.

		this->err_ref = 2; // Elevated Error

		if (this->debugbot.is_debugging() == true)
		{
			std::cout << "display_all() returned a value of " << err_code;
			std::cout << std::endl;
		}

		// This is an elevated failure because there was a memory interruption
		return this->error_detected(err_ref);
	}
	
	std::cout << "To add a tag to your HTML file, you must enter a number." << std::endl;
	std::cout << "The number displayed on the left is the number you will have to enter to use a tag," << std::endl;
	std::cout << "while the tag you will use appears to the right." << std::endl;
	std::cout << std::endl;
	std::cout << "Here are the available tags and their numbers: " << std::endl;
	std::cout << std::endl;

	for (auto i = html_tags.begin(); i != html_tags.end(); i++)
	{
		std::cout << this->html_tags.at(*t_point) << " is assigned to number " << *t_point << std::endl; // The tag and pointer should match one to one.

		t_ref += 1; // This increases "temp" which increases the value of t_point also, so it iterates
	}

	err_ref = 0;

	if (this->debugbot.is_debugging() == true)
	{
		std::cout << "display_all() returned a value of " << err_code;
		std::cout << std::endl;
	}

	return this->error_detected(err_ref);
};

int Page::maintag_begin() // Beginning of structurally significant tagging.
{
	std::cout << std::endl;
	std::cout << "Tag availability will vary greatly on different stages of the project." << std::endl;

	std::cout << "You will be given a list of available tags." << std::endl;

	std::cout << std::endl;
	std::cout << "You are on line " << this->find_line() << " of the HTML Document." << std::endl;
	std::cout << "Once you choose a tag, you will be asked to fill out other parameters." << std::endl;
	std::cout << std::endl;

	display_all(); // If display returns an error, do not continue program as normal - TODO

	std::cout << "Please select the tag you would like to use by number." << std::endl;

	std::cout << std::endl;

	this->err_ref = 0;

	if (this->debugbot.is_debugging() == true)
	{
		std::cout << "maintag_begin() returned a value of " << err_code;
		std::cout << std::endl;
	}

	return this->error_detected(err_ref);
};

int Page::subtag_begin() // Beginning of aesthetically important tagging.
{
	this->err_ref = 0;

	if (this->debugbot.is_debugging() == true)
	{
		std::cout << "subtag_begin returned a value of " << err_code;
		std::cout << std::endl;
	}

	return this->error_detected(err_ref);
};

// This could be reconfigured as a string return type but I like this setup better.
int Page::editing_process()
{
	std::cout << std::endl;
	std::cout << "Write a sentence to attach to your tag: ";

	std::cin.ignore();
	std::getline(std::cin, this->tag_filler);

	// Check for potential exceptions here -- TODO

	// Use pointers here, not references.
	this->complete_string = this->html_tags.at(*tag_pointer) + this->tag_fill() + this->html_end.at(*tag_pointer);

	std::cout << "Your completed tag is: " << this->complete_string << " !";

	std::cout << std::endl;

	this->err_ref = 0;

	if (this->debugbot.is_debugging() == true)
	{
		std::cout << "editing_process() returned a value of " << err_code;
		std::cout << std::endl;
	}

	return this->error_detected(err_ref);
};

// Don't be fooled by the name, this is just an elaborate function for modifying the META tag.
int Page::meta_process()
{
	std::cout << "This my require additional editing." << std::endl;
	std::cout << "Meta tags usually require something tacked on to the tag itself." << std::endl;
	std::cout << std::endl;
	std::cout << "What would you like to add to this tag?" << std::endl;
	std::cout << "<meta";
	this->tag_grab = "<meta";

	// In order to recycle resources and keep them relevant, use this again.
	std::cin >> this->local_hyperlink;

	if (this->local_hyperlink == "")
	{
		std::cout << "Error, no hyperlink was provided. This tag cannot be completed without one." << std::endl;
		std::cout << std::endl;

		this->err_ref = 1;

		if (this->debugbot.is_debugging() == true)
		{
			std::cout << "meta_process() returned a value of " << err_code;
			std::cout << std::endl;
		}

		return this->error_detected(err_ref);
	}

	this->link_end = "</meta>";
	this->complete_hyperlink = this->tag_grab + this->local_hyperlink + this->link_end;

	std::cout << "The completed meta tag is " << complete_hyperlink << " !" << std::endl;
	std::cout << std::endl;
	std::cout << "There is usually no need for additional text in the meta tag, so let's move on." << std::endl;

	this->err_ref = 0;

	if (this->debugbot.is_debugging() == true)
	{
		std::cout << "meta_process() returned a value of " << err_code;
		std::cout << std::endl;
	}

	return this->error_detected(err_ref);
};

int Page::hyperlink_process()
{
	std::cout << "This tag requires additional editing." << std::endl;
	std::cout << "Hyperlinks will be formatted automatically by the program, but they require a URL or file link." << std::endl;
	std::cout << std::endl;
	std::cout << "Please enter a link for this tag." << std::endl;

	if (*tag_pointer == HYPERLINK) // If normal hyperlink is being used
	{
		std::cout << "<a href= '";
		this->tag_grab = "<a href='";
	}

	std::cin >> this->local_hyperlink;

	this->complete_hyperlink = this->tag_grab + this->local_hyperlink + this->link_end;

	std::cout << "The complete hyperlink is " << this->complete_hyperlink;
	std::cout << std::endl;

	// This is where the user needs to write text in order for the hyperlink to be visited.
	std::cout << "Please enter the text associated with the hyperlink." << std::endl;
	std::cout << this->complete_hyperlink;

	std::cout << std::endl;
	std::cout << "Write a sentence to attach to your tag: ";

	std::cin.ignore();
	std::getline(std::cin, this->tag_filler);

	// Exception checking -- TODO

	this->complete_hyperlink = this->complete_hyperlink + this->tag_fill() + this->html_end.at(*tag_pointer);

	std::cout << "Your completed tag is: " << this->complete_hyperlink << " !";
	global_ref += 1;

	this->err_ref = 0;

	if (this->debugbot.is_debugging() == true)
	{
		std::cout << "hyperlink_process() returned a value of " << err_code;
		std::cout << std::endl;
	}

	return this->error_detected(err_ref);
};

// Designed to reduce clutter. This function can remain void because it should not encounter any exceptions as-is.
void Page::title_sequence()
{
	std::cout << "Creating standard HTML5 tag header..." << std::endl;
	std::cout << "Line numbers are not written to the document. They just show what lines have been processed." << std::endl;
	std::cout << std::endl;

	// This just shows the user what can't normally be seen, what's actually being written to file.
	std::cout << "Mandatory Header: " << std::endl;
	std::cout << "Line " << this->find_line() << ": "; // Pointer is already 1, so we let this be.
	std::cout << "<!DOCTYPE html>" << std::endl;
	global_ref += 1;
	std::cout << "Line " << this->find_line() << ": ";
	std::cout << "<html lang = 'en'>" << std::endl;
	global_ref += 1;
	std::cout << "Line " << this->find_line() << ": ";
	std::cout << "<head>" << std::endl;
	global_ref += 1;
	std::cout << "Line " << this->find_line() << ": ";
	std::cout << "<meta charset = 'utf-8'>" << std::endl;
	std::cout << std::endl;
};

// This public function allows all other functions to be executed privately and makes things easier to follow
void Page::setup()
{
	this->page_setup();
};

bool Page::error_detected(int &err_ref)
{
	if (err_code != 0)
	{
		if (warning_displayed == false)
		{
			show_error();
		}

		warning_displayed = true;

		return true;
	}

	return false; // Return 0, indicating that things are functioning as they should
};

// Memory management can be tricky. This function is fine as void return type.
void Page::data_cleaner()
{
	// I'll be honest with you, memory management in C++ is not my strong suit.
	// This function just wipes clean the vectors and file information regardless of general object deletion.

	this->html_tags.clear();
	this->html_end.clear();

	if (this->debugbot.is_debugging() == true)
	{
		std::cout << std::endl;
		std::cout << "Vectors wiped..." << std::endl;
	}
};

// This loop is massive because it's hard to break it into smaller pieces
int Page::tagging_loop()
{
	//std::fstream samefile;

	//try
	//{
	//	// Any strings added after this point are appended rather than directly written in
	//	samefile.open(full_file, std::ios_base::app);
	//	if (!samefile)
	//	{
	//		throw "Error opening file!";
	//	}
	//}
	//catch (const char* cstr) // If the file can't actually open, it should cut off here.
	//{
	//	std::cerr << cstr << std::endl;

	//	this->err_ref = 1;

	//	if (this->debugbot.is_debugging() == true)
	//	{
	//		std::cout << "tagging_loop() returned a value of " << err_code;
	//		std::cout << std::endl;
	//	}

	//	return this->error_detected(err_ref);
	//}

	while (this->option != "no")
	{
		std::cout << std::endl;
		std::cout << "Would you like to add another tag to your webpage?" << std::endl;
		std::cout << "Type yes or no." << std::endl;

		std::getline(std::cin, this->option);

		if (this->option == "exit") // This is an emergency exit.
		{
			std::cout << std::endl;
			std::cout << "Override recognized. Halting process." << std::endl;
			std::cout << std::endl;
			std::cout << "Program terminated prematurely due to emergency stop. Halting tagging process." << std::endl;

			err_ref = 1;
			return this->error_detected(err_ref);
		}

		if (this->option == "yes")
		{
			// Ask for a tag number - start a switch statement
			std::cout << "Please enter the tag number." << std::endl;
			std::cin >> *tag_pointer;

			if (*tag_pointer < COMMENT || *tag_pointer > XEND)
			{
				std::cout << "This input is strictly not allowed. Tag is set to NULL." << std::endl;
				std::cout << std::endl;

				*tag_pointer = XEND;
			}

			// Add functionality for TABLE, BUTTON, and so many others -- TODO
			// Finally added a proper switch statement to deal with outlier tags without simple modifications; this was a lot of work.
			switch (*tag_pointer) // This should just refer directly to tagger, which is the real variable here
			{
			// Allows HTML commenting, might be confusing using this through PageMagic
			case COMMENT:
				this->standard_tag = true;

				std::cout << "Whatever you write in the following comment will only be visible if you open the HTML page in a text editor." << std::endl;
				std::cout << "The comment will not be visible on the web page." << std::endl;

				this->editing_process();
				break;

			// Creates a web page link -- the actual tag is <a> which is why it's high on the list
			case HYPERLINK:
				this->standard_tag = false;
				// this->sub_tag = true;

				this->hyperlink_process();
				break;

			case ABBREVIATE:
				break;

			// Formats an address (not a URL, an actual home or business address)
			case ADDRESS:
				break;

			case AREA:
				break;

			// Functions a lot like <div> by dividing content to be seen as isolated from the normal page
			case ARTICLE:
				break;

			// Functions almost like <article>
			case ASIDE:
				break;

			// Provides audio via a source
			case AUDIO:
				// This is going to require a little more work than usual because audio tags are formatted slightly differently.
				//this->standard_tag = false;

				//std::cout << "Audio tags require a URL or file link to function properly." << std::endl;
				//std::cout << "Please type out the exact link of your audio file, or it will not function properly on your web page." << std::endl;
				//std::cout << std::endl;

				//this->hyperlink_process();
				break;

			case BDI:
				break;

			case BDO:
				break;

			// Creates a huge formatted quote based on the string it's given
			case BLOCKQUOTE:

				break;

			// Creates a body tag where the bulk of most content should go; not relevant as it's already present
			case BODY:
				this->standard_tag = true;

				std::cout << "Your page already has a <body> tag and may encounter problems with your browser." << std::endl;
				std::cout << "For this reason, a second <body> tag was not added. Thank you." << std::endl;
				std::cout << std::endl;

				// this->complete_string = s_state(XEND);

				this->ignore_tag = true;

				break;

			// Creates a line break, not the same as a horizontal ruler
			case BREAK:
				this->standard_tag = false;

				std::cout << "Entering this tag will be equivalent to pressing 'Enter' on the keyboard." << std::endl;
				std::cout << "This means that PageMagic will insert the next tag slightly lower on the page." << std::endl;
				std::cout << std::endl;

				this->complete_hyperlink = s_state(*tag_pointer);

				std::cout << "Your new line (break) was added." << std::endl;
				std::cout << "<br>";
				std::cout << std::endl;
				break;

			// Creates a functional button; should be paired with other tags
			case BUTTON:
				break;

			// Used for display formatting
			case CANVAS:
				break;

			// Used in assocation with an image or piece of content that needs captioning
			case CAPTION:
				break;

			case CITE:
				break;

			// Special HTML tag that isolates and displays code snippets of other languages
			case CODE:
				this->standard_tag = true;
				std::cout << "This tag will allow you to add embedded code on the webpage. Any code within this tag will only display as a string." << std::endl;
				std::cout << std::endl;

				this->editing_process();
				break;

			case COLUMN:
				break;

			case COLUMNGROUP:
				break;

			case DATA:
				break;

			case DATALIST:
				break;

			case DESCRIPTLIST:
				break;

			// Text that is omitted or intentionally altered to display that it is not relevant
			case DELETED:
				this->standard_tag = true;

				std::cout << "This tag will strike through web page text, similar to <s> but meant to emphasize rewritten statements." << std::endl;
				std::cout << "In terms of functionality, this tag and the <s> strike tag are virtually identical." << std::endl;
				std::cout << std::endl;

				this->editing_process();
				break;

			case DETAILS:
				break;

			case DEFINED:
				break;

			case DIALOG:
				break;

			// Used to divide content for special purposes; this needs a lot of work
			case DIV:
				break;

			case DESCLIST:
				break;

			case DESCTERM:
				break;

			case EMPHASIZE:
				break;

			// Creates embedded content
			case EMBED:
				break;

			case FIELDSET:
				break;

			case FIGCAPTION:
				break;

			case FIGURE:
				break;

			// Creates a specially formatted text at the bottom of the document
			case FOOTER:
				break;

			// Allows a user to create a page-defined form that can be filled out
			case FORM:
				break;

			// Header One
			case H1:
				this->standard_tag = true;

				std::cout << "This tag creates a very large heading, known as Heading 1." << std::endl;
				std::cout << std::endl;

				this->editing_process();
				break;

			// Header Two
			case H2:
				this->standard_tag = true;

				std::cout << "This tag creates a somewhat large heading, known as Heading 2." << std::endl;
				std::cout << std::endl;

				this->editing_process();
				break;

			// Header Three
			case H3:
				this->standard_tag = true;

				std::cout << "This tag creates a medium sized heading, known as Heading 3." << std::endl;
				std::cout << std::endl;

				this->editing_process();
				break;

			// Header Four
			case H4:
				this->standard_tag = true;

				std::cout << "This tag creates a heading that is a similar size to normal text, known as Heading 4." << std::endl;
				std::cout << std::endl;

				this->editing_process();
				break;

			// Header Five
			case H5:
				this->standard_tag = true;

				std::cout << "This tag creates a heading that is noticably smaller than normal text, known as Heading 5." << std::endl;
				std::cout << std::endl;

				this->editing_process();
				break;

			// Header Six
			case H6:
				this->standard_tag = true;

				std::cout << "This tag creates a heading that is relatively tiny compared to normal text, known as Heading 6." << std::endl;
				std::cout << std::endl;

				this->editing_process();
				break;

			// Contains page information and attributes including the <meta> tag
			case HEAD:
				this->standard_tag = true;

				std::cout << "Your page already has a preformatted <head> tag. Because of this, the <head> tag was not added." << std::endl;
				std::cout << std::endl;

				// this->complete_string = s_state(XEND);

				this->ignore_tag = true;

				break;

			// Not normally used outside of specific formatting; defines a page header
			case HEADER:
				break;

			// Creates a huge line across the entire HTML document
			case HORZRULER:
				this->standard_tag = false;

				std::cout << "Horizontal rulers don't require additional information." << std::endl;
				std::cout << "They generate long thin lines across an HTML page." << std::endl;
				std::cout << std::endl;

				this->complete_hyperlink = s_state(*tag_pointer);
				break;

			// The root tag of the html document
			case HTMLROOT: // This is automatically provided by the program and should never be used twice
				this->standard_tag = true;

				std::cout << "The <html> tag should never be added a second time in a webpage document." << std::endl;
				std::cout << "It is a root tag that is meant to be used before any HTML is written to the page." << std::endl;
				std::cout << "Because of this, the <html> tag was not added." << std::endl;
				std::cout << std::endl;

				// this->complete_string = s_state(XEND);

				this->ignore_tag = true;

				break;

			case ITALICS:
				this->standard_tag = true;

				std::cout << "This sentence will be italicized and appear with italics formatting when displayed in a web browser." << std::endl;
				std::cout << std::endl;

				this->editing_process();
				break;

			case IFRAME:
				break;

			// Creates an image linked to an image source
			case IMG:
				break;

			case INPUT:
				break;

			case INS:
				break;

			case KEYBOARD:
				break;

			case LABEL:
				break;

			case LEGEND:
				break;

			case LISTITEM:
				break;

			case LINK:
				break;

			// Defines the main content of a page, usually to draw attention from a user
			case MAIN:
				this->standard_tag = true;

				std::cout << "This tag will focus inputted text as the main scope of a web page." << std::endl;
				std::cout << std::endl;

				this->editing_process();
				break;

			case IMGMAP:
				break;

			case MARK:
				break;

			// Sets information for page display or attributes
			case META:
				this->standard_tag = false;

				this->meta_process();
				break;

			case METER:
				break;

			// Object usually formatted for user navigation
			case NAV:
				break;

			// The web page displays this message on a web browser when JavaScript is disabled
			case NOSCRIPT:
				break;

			case OBJECT:
				break;

			// Creates an ordered list that displays numbers
			case ORDERLIST:
				break;

			case OPTGROUP:
				break;

			case OPTION:
				break;

			case OUTPUT:
				break;

			// Very common tag used to denote a paragraph of text; should really be paired with other functional tags
			case PARAGRAPH:
				this->standard_tag = true;

				std::cout << "This tag will allow you to input text in the form of a paragraph." << std::endl;
				std::cout << std::endl;

				this->editing_process();
				break;

			case PARAMETER:
				break;

			// Similar functionality to IMG
			case PICTURE:
				break;

			case PREFORMAT:
				break;

			// Used to create progress bars and such
			case PROGRESS:
				break;

			// Creates a small and specially formatted short quote string
			case SHORTQUOTE:
				break;

			// If Ruby is not present on this page but is relevant to the web page itself, this tag becomes relevant
			case NORUBY:
				this->standard_tag = true;

				std::cout << "Putting this tag in your HTML document show text that will display if a user's browser doesn't support Ruby annotations." << std::endl;
				std::cout << std::endl;

				this->editing_process();
				break;
				// Creates text with a line straight through it
			case STRIKEOUT:
				break;

			case SAMPLE:
				break;

			// Allows for custom JavaScript or other programming elements
			case SCRIPT:
				break;

			// Creates a section of relevant data, images, video, or text
			case SECTION:
				break;

			case SELECT:
				break;

			// Formats text to be small
			case SMALL:
				break;

			// Creates a linked source object
			case SOURCE:
				break;

			// Functions sort of like <div> or <style> but shorter
			case SPAN:
				break;

			// Creates specially formatted bold text
			case STRONGTEXT:
				this->standard_tag = true;

				std::cout << "The sentence will be formatted on your HTML document to appear bold and vivid." << std::endl;
				std::cout << "If used within a paragraph, it should follow paragraph formatting." << std::endl;

				this->editing_process();
				break;

			// Used for custom CSS
			case STYLE:
				// This tag is mostly functionally useless without something to actually attach it to. This needs to be pairable with other tags. - TODO

				break;

				// Forces text to look small
			case SUBSCRIPT:
				this->standard_tag = true;

				std::cout << "This sentence will be formatted into subscript, which makes it appear much smaller." << std::endl;
				std::cout << "In most cases, this also means the text will appear aligned to the bottom area of where it would normally be." << std::endl;
				std::cout << std::endl;

				this->editing_process();
				break;

			// Creates a summary text object
			case SUMMARY:
				break;

			// Forces text to look like an exponent
			case SUPERSCRIPT:
				this->standard_tag = true;

				std::cout << "This sentence will be formatted into superscript, which makes it appear much smaller." << std::endl;
				std::cout << "In most cases, this also means the text will appear aligned to the top area of where it would normally be." << std::endl;
				std::cout << std::endl;

				this->editing_process();
				break;

			// SVG is a type of canvas object
			case SVG:
				break;

			// Creates a table. Because this is a complex tag, requires more data
			case TABLE:
				break;

			// Table body, should be coupled with TABLE
			case TBODY:
				break;

			// Individual table cell, should be coupled with TABLE and others
			case TABLECELL:
				break;

			case TEMPLATE:
				break;

			case TEXTAREA:
				break;

			// Table footer, should be coupled with TABLE
			case TABLEFOOT:
				break;

			// Table header; should be coupled with TABLE
			case TABLEHEAD:
				break;

			// Table header extended
			case THEADCONT:
				break;

			// Creates a time object for HTML page
			case TIME:
				this->standard_tag = true;

				std::cout << "Formatted time variable will be added to the document as-is, no further input is required." << std::endl;
				std::cout << std::endl;

				break;

			case TITLE: // This is unnecessary, the user is prompted during page_setup, but included for stability
				this->standard_tag = true;

				std::cout << "There is no need to add a <title> tag, because it was assigned during document creation." << std::endl;
				std::cout << "The <title> tag was not added." << std::endl;

				this->ignore_tag = true;

				break;

			// Creates and fills a table row with relevant information
			case TABLEROW: // This should be coupled with TABLE
				break;

			case TRACK:
				break;

			// Creates an unordered list
			case UNORDERLIST:
				// This needs to be paired with actual list elements at some point. It's useless without them. - TODO


				break;

			case VARIABLE:
				break;

			// Links a video via a source
			case VIDEO:
				break;

			// Creates a line break; NOT the same as <hr>
			case WEBLINEBREAK:
				break;

			case XEND: // Don't actually use this. This tag helps with program functionality. Can't hide it either or it breaks display.
				this->standard_tag = true;

				std::cout << "This tag is filler and is not used on HTML pages." << std::endl;
				std::cout << "It is included in the tag list to prevent program errors." << std::endl;
				std::cout << std::endl;
				std::cout << "Thank you for your understanding." << std::endl;

				this->ignore_tag = true;

				break;

			default:
				std::cout << std::endl;
				std::cout << "This tag number was not recognized or is invalid, please try again." << std::endl;
				break;
			}

			std::cout << std::endl;
			std::cout << "You entered: " << *tag_pointer << std::endl;
			std::cout << "Adding the " << this->s_state(*tag_pointer) << " tag if applicable." << std::endl;

			this->tag_grab = this->s_state(*tag_pointer); // Direct assignment. Seems to work for the purpose of this program.

			if (this->debugbot.is_debugging() == true)
			{
				std::cout << std::endl;
				std::cout << "DEBUG: " << "tag_grab is assigned to " << this->tag_grab << std::endl;
				std::cout << std::endl;
			}

			if (this->ignore_tag == true) // This is a rare sequence reserved for tags that don't belong in documents
			{
				*tag_pointer = XEND; // The tag is forcefully changed to NULL

				std::cout << std::endl;
				std::cout << "This tag is not valid to be used on this document." << std::endl;
				std::cout << "The program has ignored your tag input to either: save on resources, prevent errors, or clean up your document." << std::endl;
				std::cout << "Thank you for your understanding." << std::endl;

				*global_point -= 1; // Removes a line because this could not execute, that way it still breaks even at 0. Do not use ref for this, just in case.

				this->ignore_tag = false; // Set to false afterward so the next tag can be valid.
			}

			if (this->standard_tag == true) // Use the standard tag output to HTML
			{
				std::cout << std::endl;
				std::cout << "The last line you added was: " << complete_string;
				std::cout << std::endl;

				if (*tag_pointer != XEND) // If the tag is a valid tag and not filler
				{
					manager.file_write(this->complete_string);
				}
				else
				{
					if (this->debugbot.is_debugging() == true)
					{
						std::cout << "The tag position was XEND / NULL and was ignored.";
					}

					std::cout << std::endl;
					std::cout << "Invalid entry." << std::endl;
					std::cout << "Skipping tag..." << std::endl;
					std::cout << std::endl;
				}
			}

			else if (this->standard_tag == false) // Use the hyperlink style tag output to HTML
			{
				std::cout << std::endl;
				std::cout << "You added " << complete_hyperlink;
				std::cout << std::endl;

				manager.file_write(this->complete_hyperlink);
			}

			if (sub_tag == true) // If a sub-tagging process is finished, reset it
			{
				sub_tag = false;
			}

			// File always writes the data when finished.
			global_ref += 1;

			this->local_hyperlink.clear();
			this->tag_grab.clear();
			this->complete_hyperlink.clear();

			// Create a standardized function that can be used for most of the other tags. TODO

		}
		else if (this->option == "no")
		{
			std::cout << "Progress was saved to file." << std::endl;
			std::cout << "Command recognized. Halting tagging process..." << std::endl;
			std::cout << std::endl;
		}
		else
		{
			std::cout << "This command was not recognized. Please try again." << std::endl;
			std::cout << "If you entered 'no' then this process will stop immediately regardless." << std::endl;
			std::cout << std::endl;
		}

		// Once this loop is broken, the Page object exits after program finishes deploying the full HTML.
	};

	// Close the file once more, prepare for final append.
	// samefile.close();

	err_ref = 0;

	if (this->debugbot.is_debugging() == true)
	{
		std::cout << "tagging_loop() returned a value of " << err_code;
		std::cout << std::endl;
	}

	return this->error_detected(err_ref);
};

int Page::tag_finish()
{
	std::cout << "All done with tagging! Finishing document cleanup..." << std::endl;

	std::cout << "Writing body end tag..." << std::endl;
	std::cout << std::endl;
	std::cout << "</body>" << std::endl;

	manager.file_write(""); // Write nothing and append a newline
	manager.file_write("</body>");

	// This runs when the program is finished tagging.
	std::cout << "Writing HTML end tag..." << std::endl;
	std::cout << std::endl;
	std::cout << "</html>" << std::endl;

	manager.file_write("");
	manager.file_write("</html>");

	global_ref += 2; // Writing the end tags counts as more lines

	std::cout << std::endl;
	std::cout << "Lines wrapped up at " << find_line() << ".";
	std::cout << std::endl;

	manager.close_file(); // Make sure the file is closed.

	this->err_ref = 0;

	if (this->debugbot.is_debugging() == true)
	{
		std::cout << "tag_finish() returned a value of " << err_code;
		std::cout << std::endl;
	}

	return this->error_detected(err_ref);
};

// It was too difficult to set up private functions within this one so it's all lumped in together.
int Page::page_setup() // Tags the beginning of an HTML document with proper heading.
{
	manager.file_process(); // Start the file editing process

	if (manager.error_state != 0)
	{
		std::cout << "Page Setup was cancelled due to an error." << std::endl;

		err_ref = manager.error_state;
		return this->error_detected(err_ref);
	}

	std::cout << "Writing to file: " << manager.full_file << std::endl;

	this->title_sequence();

	// File should be written with standard head tags. This is automatically configured for HTML5 in English.
	// Lines are ACTUALLY written here but displayed earlier for reasons of convenience.
	manager.file_write("<!DOCTYPE html>");
	manager.file_write("<html lang = 'en'>");
	manager.file_write("<head>");
	manager.file_write("<meta charset = 'utf-8'>");

	if (this->debugbot.is_debugging() == true)
	{
		std::cout << std::endl;
		std::cout << "DEBUG: " << std::endl;
		std::cout << "Document lines written so far: " << find_line() << std::endl;
		std::cout << std::endl;
	}

	std::cout << "Starting title naming process..." << std::endl;
	std::cout << std::endl;
	std::cout << "What would you like the title of this webpage to be?" << std::endl;

	std::cout << "Page Title: ";

	std::cin.ignore();
	std::getline(std::cin, this->title_header);

	if (this->title_header == "")
	{
		std::cout << std::endl;
		std::cout << "There was an error and no input was detected!" << std::endl;
		std::cout << std::endl;
		std::cout << "Reminder: This program is experimental and some bugs may still be present." << std::endl;
		std::cout << std::endl;
		std::cout << "The program connot successfully continue this operation. Please try again later." << std::endl;

		this->err_ref = 1;
		return this->error_detected(err_ref);
	}

	std::cout << std::endl;

	std::cout << "Your output was recorded as " << this->get_title() << std::endl;

	manager.file_write("<title>");
	manager.file_write(this->title_header);
	manager.file_write("</title>");
	global_ref += 3; // Because of the new file writing system additional lines are added.

	system("pause"); // Pause to allow the user to read what's happening.

	this->maintag_begin(); // Declares tags but they can't actually be used in scope unless it's page_setup()

	std::cout << std::endl;
	std::cout << "Please remember to add the <head> and <body> tags in order for the page to be fully functional." << std::endl;
	std::cout << "If you need more information on how to build webpages in general, please consult the information at " << std::endl;
	std::cout << "https://www.w3schools.com/" << std::endl;
	std::cout << "Copy and paste the link to your browser to go there!" << std::endl;
	std::cout << std::endl;

	std::cout << "The <head> tag of your HTML document has already been created. Creating a <body> tag..." << std::endl;

	manager.file_write("<body>");
	global_ref += 1;

	std::cout << "<body>" << std::endl;
	std::cout << std::endl;

	// The file would have originally closed here, but the execution has changed.
	// file.close();

	this->page_explain(); // Shortens an explanation.

	tagging_loop();

	// All of this is just finalization and finishing touches to the document.

	if (err_ref == 0)
	{
		tag_finish();
	}
	else
	{
		std::cout << std::endl;
		std::cout << "There were errors during program runtime and this process must be halted." << std::endl;
		std::cout << std::endl;

		this->err_ref = 1;
		return this->error_detected(err_ref);
	}

	this->err_ref = 0;

	if (this->debugbot.is_debugging() == true)
	{
		std::cout << "page_setup() returned a value of " << err_code;
		std::cout << std::endl;
	}

	return this->error_detected(err_ref);
};

// Doesn't actually do anything, just explains what's going on for the user.
void const Page::page_explain()
{
	std::cout << "When you are finished, a matching </body> tag will be added to the end of the document." << std::endl;
	std::cout << "The </html> tag will also be added automatically." << std::endl;
	std::cout << "This will make it possible for the page to be visible in a web browser." << std::endl;
	std::cout << std::endl;
	std::cout << "The program will pause here to give you a minute to catch up." << std::endl;
	system("pause"); // Give the user a chance to read what's going on.
};

// Returns true when successful and false when not.
int Page::start_file()
{
	manager.file_created();

	if (manager.error_state != 0) // Unclean exit
	{
		this->err_ref = manager.error_state;

		return error_detected(err_ref);
	}
	else
	{
		this->err_ref = 0;

		return error_detected(err_ref);
	}
};