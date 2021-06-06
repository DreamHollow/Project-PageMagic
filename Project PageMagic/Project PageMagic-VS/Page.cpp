#include "Page.h"

Page::Page()
{
	this->temp = 0;
	t_point = &temp;

	this->page_debug = false;

	this->global_line = 1;
	global_point = &global_line; // Do NOT try to delete these kinds of pointers. Learned the hard way.

	this->tagger = 0;
	this->p_tag = &tagger; // I'm a little happy-go-lucky with pointers here, sorry.

	this->option = 'a'; // Initialized to junk, is set during function.

	this->initialize_tags();
};

Page::~Page()
{
	// I feel better having this function do some general cleanup on exit.
	memory_cleaner();
};

void Page::initialize_tags()
{

	// There are an absolutely MASSIVE amount of HTML tags. I didn't even know some of these existed.
	// Enum will keep track of which tags to deploy, vector will fill the tags.
	html_tags.push_back("<!--"); // 0; Very different from most tags
	html_tags.push_back("<a>"); // 1; Must be modified to contain a value like a URL
	html_tags.push_back("<abbr>"); // 2
	html_tags.push_back("<address>"); // 3
	html_tags.push_back("<area>"); // 4
	html_tags.push_back("<article>"); // 5
	html_tags.push_back("<aside>"); // 6
	html_tags.push_back("<audio>"); // 7; Must be modified
	html_tags.push_back("<bdi>"); // 8
	html_tags.push_back("<bdo>"); // 9
	html_tags.push_back("<blockquote>"); // 10
	html_tags.push_back("<body>"); // 11; this tag should really be included before ALL content.
	html_tags.push_back("<br>"); // 12; line break
	html_tags.push_back("<button>"); // 13
	html_tags.push_back("<canvas>"); // 14
	html_tags.push_back("<caption>"); // 15; accessibility options
	html_tags.push_back("<cite>"); // 16
	html_tags.push_back("<code>"); // 17; very important to programmers
	html_tags.push_back("<col>"); // 18
	html_tags.push_back("<colgroup>"); // 19; contains a group of columns
	html_tags.push_back("<data>"); // 20; allows machine readable code
	html_tags.push_back("<datalist>"); // 21
	html_tags.push_back("<dd>"); // 22
	html_tags.push_back("<del>"); // 23
	html_tags.push_back("<details>"); // 24
	html_tags.push_back("<dfn>"); // 25
	html_tags.push_back("<dialog>"); // 26
	html_tags.push_back("<div>"); // 27
	html_tags.push_back("<dl>"); // 28
	html_tags.push_back("<dt>"); // 29
	html_tags.push_back("<em>"); // 30
	html_tags.push_back("<embed>"); // 31
	html_tags.push_back("<fieldset>"); // 32
	html_tags.push_back("<figcaption>"); // 33
	html_tags.push_back("<figure>"); // 34
	html_tags.push_back("<footer>"); // 35
	html_tags.push_back("<form>"); // 36
	html_tags.push_back("<h1>"); // 37
	html_tags.push_back("<h2>"); // 38
	html_tags.push_back("<h3>"); // 39
	html_tags.push_back("<h4>"); // 40
	html_tags.push_back("<h5>"); // 41
	html_tags.push_back("<h6>"); // 42
	html_tags.push_back("<head>"); // 43
	html_tags.push_back("<header>"); // 44
	html_tags.push_back("<hr>"); // 45
	html_tags.push_back("<html>"); // 46; INVALID - ROOT
	html_tags.push_back("<i>"); // 47
	html_tags.push_back("<iframe>"); // 48
	html_tags.push_back("<img>"); // 49; requires modification
	html_tags.push_back("<input>"); // 50
	html_tags.push_back("<ins>"); // 51
	html_tags.push_back("<kbd>"); // 52
	html_tags.push_back("<label>"); // 53
	html_tags.push_back("<legend>"); // 54
	html_tags.push_back("<li>"); // 55
	html_tags.push_back("<link>"); // 56
	html_tags.push_back("<main>"); // 57
	html_tags.push_back("<map>"); // 58
	html_tags.push_back("<mark>"); // 59
	html_tags.push_back("<meta>"); // 60
	html_tags.push_back("<meter>"); // 61
	html_tags.push_back("<nav>"); // 62
	html_tags.push_back("<noscript>"); // 63
	html_tags.push_back("<object>"); // 64
	html_tags.push_back("<ol>"); // 65
	html_tags.push_back("<optgroup"); // 66
	html_tags.push_back("<option>"); // 67
	html_tags.push_back("<output>"); // 68
	html_tags.push_back("<p>"); // 69
	html_tags.push_back("<param>"); // 70
	html_tags.push_back("<picture>"); // 71
	html_tags.push_back("<pre>"); // 72
	html_tags.push_back("<progress>"); // 73
	html_tags.push_back("<q>"); // 74
	html_tags.push_back("<rp>"); // 75; "no ruby"
	html_tags.push_back("<s>"); // 76
	html_tags.push_back("<samp>"); // 77
	html_tags.push_back("<script>"); // 78
	html_tags.push_back("<section>"); // 79
	html_tags.push_back("<select>"); // 80
	html_tags.push_back("<small>"); // 81
	html_tags.push_back("<source>"); // 82
	html_tags.push_back("<span>"); // 83
	html_tags.push_back("<strong>"); // 84
	html_tags.push_back("<style>"); // 85
	html_tags.push_back("<sub>"); // 86
	html_tags.push_back("<summary>"); // 87
	html_tags.push_back("<sup>"); // 88
	html_tags.push_back("<svg>"); // 89
	html_tags.push_back("<table>"); // 90
	html_tags.push_back("<tbody>"); // 91
	html_tags.push_back("<td>"); // 92
	html_tags.push_back("<template>"); // 93
	html_tags.push_back("<textarea>"); // 94
	html_tags.push_back("<tfoot>"); // 95
	html_tags.push_back("<th>"); // 96
	html_tags.push_back("<thead>"); // 97
	html_tags.push_back("<time>"); // 98
	html_tags.push_back("<title>"); // 99; INVALID
	html_tags.push_back("<tr>"); // 100
	html_tags.push_back("<track>"); // 101
	html_tags.push_back("<ul>"); // 102
	html_tags.push_back("<var>"); // 103
	html_tags.push_back("<video>"); // 104
	html_tags.push_back("<wbr>"); // 105



	// Matching all of the opening tags to the closing tags.
	html_end.push_back("-->"); // 0
	html_end.push_back("</a>"); // 1; Must be modified to contain a value like a URL
	html_end.push_back("</abbr>"); // 2
	html_end.push_back("</address>"); // 3
	html_end.push_back("</area>"); // 4
	html_end.push_back("</article>"); // 5
	html_end.push_back("</aside>"); // 6
	html_end.push_back("</audio>"); // 7; Must be modified
	html_end.push_back("</bdi>"); // 8
	html_end.push_back("</bdo>"); // 9
	html_end.push_back("</blockquote>"); // 10
	html_end.push_back("</body>"); // 11; this tag should really be included before ALL content.
	html_end.push_back("</br>"); // 12; line break
	html_end.push_back("</button>"); // 13
	html_end.push_back("</canvas>"); // 14
	html_end.push_back("</caption>"); // 15; accessibility options
	html_end.push_back("</cite>"); // 16
	html_end.push_back("</code>"); // 17; very important to programmers
	html_end.push_back("</col>"); // 18
	html_end.push_back("</colgroup>"); // 19; contains a group of columns
	html_end.push_back("</data>"); // 20; allows machine readable code
	html_end.push_back("</datalist>"); // 21
	html_end.push_back("</dd>"); // 22
	html_end.push_back("</del>"); // 23
	html_end.push_back("</details>"); // 24
	html_end.push_back("</dfn>"); // 25
	html_end.push_back("</dialog>"); // 26
	html_end.push_back("</div>"); // 27
	html_end.push_back("</dl>"); // 28
	html_end.push_back("</dt>"); // 29
	html_end.push_back("</em>"); // 30
	html_end.push_back("</embed>"); // 31
	html_end.push_back("</fieldset>"); // 32
	html_end.push_back("</figcaption>"); // 33
	html_end.push_back("</figure>"); // 34
	html_end.push_back("</footer>"); // 35
	html_end.push_back("</form>"); // 36
	html_end.push_back("</h1>"); // 37
	html_end.push_back("</h2>"); // 38
	html_end.push_back("</h3>"); // 39
	html_end.push_back("</h4>"); // 40
	html_end.push_back("</h5>"); // 41
	html_end.push_back("</h6>"); // 42
	html_end.push_back("</head>"); // 43
	html_end.push_back("</header>"); // 44
	html_end.push_back("</hr>"); // 45
	html_end.push_back("</html>"); // 46; INVALID - ROOT
	html_end.push_back("</i>"); // 47
	html_end.push_back("</iframe>"); // 48
	html_end.push_back("</img>"); // 49; requires modification
	html_end.push_back("</input>"); // 50
	html_end.push_back("</ins>"); // 51
	html_end.push_back("</kbd>"); // 52
	html_end.push_back("</label>"); // 53
	html_end.push_back("</legend>"); // 54
	html_end.push_back("</li>"); // 55
	html_end.push_back("</link>"); // 56
	html_end.push_back("</main>"); // 57
	html_end.push_back("</map>"); // 58
	html_end.push_back("</mark>"); // 59
	html_end.push_back("</meta>"); // 60
	html_end.push_back("</meter>"); // 61
	html_end.push_back("</nav>"); // 62
	html_end.push_back("</noscript>"); // 63
	html_end.push_back("</object>"); // 64
	html_end.push_back("</ol>"); // 65
	html_end.push_back("</optgroup"); // 66
	html_end.push_back("</option>"); // 67
	html_end.push_back("</output>"); // 68
	html_end.push_back("</p>"); // 69
	html_end.push_back("</param>"); // 70
	html_end.push_back("</picture>"); // 71
	html_end.push_back("</pre>"); // 72
	html_end.push_back("</progress>"); // 73
	html_end.push_back("</q>"); // 74
	html_end.push_back("</rp>"); // 75; "no ruby"
	html_end.push_back("</s>"); // 76
	html_end.push_back("</samp>"); // 77
	html_end.push_back("</script>"); // 78
	html_end.push_back("</section>"); // 79
	html_end.push_back("</select>"); // 80
	html_end.push_back("</small>"); // 81
	html_end.push_back("</source>"); // 82
	html_end.push_back("</span>"); // 83
	html_end.push_back("</strong>"); // 84
	html_end.push_back("</style>"); // 85
	html_end.push_back("</sub>"); // 86
	html_end.push_back("</summary>"); // 87
	html_end.push_back("</sup>"); // 88
	html_end.push_back("</svg>"); // 89
	html_end.push_back("</table>"); // 90
	html_end.push_back("</tbody>"); // 91
	html_end.push_back("</td>"); // 92
	html_end.push_back("</template>"); // 93
	html_end.push_back("</textarea>"); // 94
	html_end.push_back("</tfoot>"); // 95
	html_end.push_back("</th>"); // 96
	html_end.push_back("</thead>"); // 97
	html_end.push_back("</time>"); // 98
	html_end.push_back("</title>"); // 99; INVALID
	html_end.push_back("</tr>"); // 100
	html_end.push_back("</track>"); // 101
	html_end.push_back("</ul>"); // 102
	html_end.push_back("</var>"); // 103
	html_end.push_back("</video>"); // 104
	html_end.push_back("</wbr>"); // 105
};

std::string Page::s_state(int num)
{
	return this->html_tags.at(num); // Return the HTML tag at the appropriate number.
};

// Exists purely for debugging.
void Page::display_all()
{
	// None of these variables need to be used beyond the scope of this function.

	if (t_point == nullptr)
	{
		std::cout << "Error, no memory could be allocated to this pointer!";
		std::cout << std::endl;

		exit(1);
	}
	
	std::cout << "To add a tag to your HTML file, you must enter a number." << std::endl;
	std::cout << "The number displayed on the left is the number you will have to enter to use a tag," << std::endl;
	std::cout << "while the tag you will use appears to the right." << std::endl;
	std::cout << std::endl;
	std::cout << "Here are the available numbers - tags: " << std::endl;
	std::cout << std::endl;

	for (auto i = html_tags.begin(); i != html_tags.end(); i++)
	{
		std::cout << this->html_tags.at(*t_point) << " is assigned to number " << *t_point << std::endl; // The tag and pointer should match one to one.

		*t_point += 1;
	}
};

void Page::tag_begin() // Messed around with enum scopes until I found an appropriate one.
{
	std::cout << std::endl;
	std::cout << "Tag availability will vary greatly on different stages of the project." << std::endl;

	std::cout << "You will be given a list of available tags." << std::endl;

	std::cout << std::endl;
	std::cout << "You are on line " << find_line() << " of the HTML Document." << std::endl;
	std::cout << "Once you choose a tag, you will be asked to fill out other parameters." << std::endl;
	std::cout << std::endl;

	display_all();

	std::cout << "Please select the tag you would like to use by number." << std::endl;

	std::cout << std::endl;
};

void Page::editing_process()
{
	std::cout << std::endl;
	std::cout << "Write a sentence to attach to your tag: ";
	std::cin.ignore();
	std::cin.getline(this->tag_filler, 500);

	this->complete_string = this->html_tags.at(*p_tag) + this->tag_fill() + this->html_end.at(*p_tag);

	std::cout << "Your completed tag is: " << this->complete_string << " !";

	std::cout << std::endl;
};

// Don't be fooled by the name, this is just an elaborate function for modifying the META tag.
void Page::meta_process()
{
	std::cout << "This my require additional editing." << std::endl;
	std::cout << "Meta tags usually require something tacked on to the tag itself." << std::endl;
	std::cout << std::endl;
	std::cout << "What would you like to add to this tag?" << std::endl;
	std::cout << "<meta";
	this->tag_grab = "<meta";

	// In order to recycle resources and keep them relevant, use this again.
	std::cin >> this->local_hyperlink;

	this->link_end = "</meta>";
	this->complete_hyperlink = this->tag_grab + this->local_hyperlink + this->link_end;

	std::cout << "The completed meta tag is " << complete_hyperlink << " !" << std::endl;
	std::cout << std::endl;
	std::cout << "There is usually no need for additional text in the meta tag, so let's move on." << std::endl;
};

void Page::hyperlink_process()
{
	

	std::cout << "This tag requires additional editing." << std::endl;
	std::cout << "Hyperlinks will be formatted automatically by the program, but they require a website URL." << std::endl;
	std::cout << std::endl;
	std::cout << "Please enter a URL." << std::endl;
	std::cout << "<a href= '";
	this->tag_grab = "<a href='";

	// No spaces should be necessary here so a regular string should work fine.
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
	std::cin.getline(tag_filler, 500);

	this->complete_hyperlink = this->complete_hyperlink + this->tag_fill() + this->html_end.at(*p_tag);

	std::cout << "Your completed tag is: " << complete_hyperlink << " !";
	*global_point += 1;
};

// Returns the tag_filler as a string
std::string Page::tag_fill() // This function is called when a tag needs filler.
{
	return this->tag_filler; // Return the string to be implemented as filler.
};

void Page::declare(std::string local_file) // Declaration should always just emphasize that a file exists and is accessible.
{
	if(std::ifstream(local_file))
	{
		std::cout << local_file + " was validated successfully." << std::endl;
	}
	else
	{
		std::cout << "There was a problem with validating the file name. Please double check file parameters." << std::endl;
		std::cout << std::endl;
	}
}

// Designed to reduce clutter. This part is mostly visual anyway.
void Page::title_sequence()
{
	std::cout << "Creating standard HTML5 tag header..." << std::endl;
	std::cout << "Line numbers are not written to the document. They just show what lines have been processed." << std::endl;
	std::cout << std::endl;

	// This just shows the user what can't normally be seen, what's actually being written to file.
	std::cout << "Mandatory Header: " << std::endl;
	std::cout << "Line " << this->find_line() << ": "; // Pointer is already 1, so we let this be.
	std::cout << "<!DOCTYPE html>" << std::endl;
	*global_point += 1;
	std::cout << "Line " << this->find_line() << ": ";
	std::cout << "<html lang = 'en'>" << std::endl;
	*global_point += 1;
	std::cout << "Line " << this->find_line() << ": ";
	std::cout << "<head>" << std::endl;
	*global_point += 1;
	std::cout << "Line " << this->find_line() << ": ";
	std::cout << "<meta charset = 'utf-8'>" << std::endl;
	std::cout << std::endl;
};

void Page::setup() // This function defines what happens with a file. Not to be confused with page_setup() which is more verbose.
{
	// Starts calling private functions for page initialization
	this->page_setup();
};

// Memory management for this program is a bit of a nightmare. I want to plug any leaks.
void Page::memory_cleaner()
{
	// I'll be honest with you, memory management in C++ is not my strong suit.

	this->html_tags.clear(); // Delete all HTML tags on exit, just to be sure.
	this->html_end.clear();

	if (this->page_debug == true)
	{
		std::cout << std::endl;
		std::cout << "Page object being deconstructed..." << std::endl;
	}

	// If the full_file string still holds information, clear it.
	if (!full_file.empty())
	{
		full_file.clear();
	}
};

// It was too difficult to set up private functions within this one so it's all lumped in together.
void Page::page_setup() // Tags the beginning of an HTML document with proper heading.
{
	// Tried some exception handling here.
	std::fstream outfile;

	try
	{
		outfile.open(full_file, std::ios::in | std::ios::out);
		if (!outfile)
		{
			throw "Error opening file!";
		}
	}
	catch(const char* cstr) // Display exception message.
	{
		std::cerr << cstr << std::endl;
	}

	std::cout << "Writing to file: " << full_file << std::endl;

	title_sequence();

	// File should be written with standard head tags. This is automatically configured for HTML5 in English.
	// Lines are ACTUALLY written here but displayed earlier for reasons of convenience.
	outfile << "<!DOCTYPE html>" << std::endl;
	outfile << "<html lang = 'en'>" << std::endl;
	outfile << "<head>" << std::endl;
	outfile << "<meta charset = 'utf-8'>" << std::endl;

	if (this->page_debug == true)
	{
		std::cout << std::endl;
		std::cout << "DEBUG: " << std::endl;
		std::cout << "Document lines written so far: " << find_line() << std::endl;
		std::cout << std::endl;
	}

	std::cout << "Starting title naming process..." << std::endl;
	std::cout << std::endl;
	std::cout << "What would you like the title of this webpage to be?" << std::endl;
	// This is no longer true! Try not to exceed 50 characters, though.
	// std::cout << "Please use a single word title for now. The program has problems recording space bar input." << std::endl;

	std::cout << "Page Title: ";

	std::cin.ignore();
	std::cin.getline(this->title_header, 50);

	if (this->title_header == "")
	{
		std::cout << std::endl;
		std::cout << "There was an error and no input was detected." << std::endl;
		std::cout << "Reminder: This program is experimental and some bugs may still be present." << std::endl;
		std::cout << std::endl;
		std::cout << "The program connot successfully continue this operation. Please try again later." << std::endl;

		exit(1);
	}

	std::cout << std::endl;

	std::cout << "Your output was recorded as " << this->get_title() << std::endl;

	outfile << "<title>" << this->title_header << "</title>" << std::endl;
	*global_point += 1; // Another line written in. This one closes on it's own.

	system("pause"); // Pause to allow the user to read what's happening.

	this->tag_begin(); // Declares tags but they can't actually be used in scope unless it's page_setup()

	std::cout << std::endl;
	std::cout << "Please remember to add the <head> and <body> tags in order for the page to be fully functional." << std::endl;
	std::cout << "If you need more information on how to build webpages in general, please consult the information at " << std::endl;
	std::cout << "https://www.w3schools.com/" << std::endl;
	std::cout << "Copy and paste the link to your browser to go there!" << std::endl;
	std::cout << std::endl;

	std::cout << "The <head> tag of your HTML document has already been created. Creating a <body> tag..." << std::endl;

	outfile << "<body>" << std::endl;
	*global_point += 1;

	std::cout << "<body>" << std::endl;
	std::cout << std::endl;

	this->page_explain(); // Shortens an explanation.

	// While the user has not entered "n" as a response.
	while (this->option != 'n')
	{
		std::cout << std::endl;
		std::cout << "Would you like to add another tag to your webpage?" << std::endl;
		std::cout << "Type y for yes, n for no." << std::endl;
		std::cin >> option;

		if (this->option == 'y')
		{
			// Ask for a tag number - start a switch statement
			std::cout << "Please enter the tag number." << std::endl;
			std::cin >> *p_tag;

			// These two are the only ones that are preformatted to be included besides the mandatory header
			if (*p_tag == HEAD)
			{
				std::cout << std::endl;
				std::cout << "Your page already has a preformatted <head> tag, are you sure about this?" << std::endl;
				std::cout << std::endl;
			}
			else if (*p_tag == BODY)
			{
				std::cout << std::endl;
				std::cout << "Your page already has a <body> tag and may encounter problems with your browser." << std::endl;
				std::cout << std::endl;
			}

			std::cout << std::endl;
			std::cout << "You entered: " << *p_tag << std::endl;
			std::cout << "Adding the " << this->s_state(*p_tag) << " tag." << std::endl;

			this->tag_grab = this->s_state(*p_tag); // Direct assignment. Seems to work for the purpose of this program.

			if (this->page_debug == true)
			{
				std::cout << std::endl;
				std::cout << "DEBUG: " << "tag_grab is assigned to " << this->tag_grab << std::endl;
				std::cout << std::endl;
			}

			// Begin tag specification.

			// User is prompted to write out a string. This step will be skipped if a unique type is triggered.
			if (*p_tag == HYPERLINK)
			{
				standard_tag = false;

				this->hyperlink_process();
			}
			else if (*p_tag == BREAK)
			{
				standard_tag = false;

				std::cout << "Entering this tag will be equivalent to pressing 'Enter' on the keyboard." << std::endl;
				std::cout << "This means that PageMagic will insert the next tag slightly lower on the page." << std::endl;
				std::cout << std::endl;

				this->complete_hyperlink = s_state(*p_tag);

				std::cout << "Your new line (break) was added." << std::endl;
				std::cout << "<br>";
				std::cout << std::endl;
			}
			else if (*p_tag == HORZRULER)
			{
				standard_tag = false;

				std::cout << "Horizontal rulers don't require additional information." << std::endl;
				std::cout << "They generate long thin lines across an HTML page." << std::endl;
				std::cout << std::endl;

				this->complete_hyperlink = s_state(*p_tag);
			}
			else if (*p_tag == META)
			{
				standard_tag = false;

				this->meta_process();
			}
			else // Do a standard tagging process.
			{
				standard_tag = true;

				if (this->page_debug == true)
				{
					std::cout << std::endl;
					std::cout << "DEBUG: Encountered else statement for standard tags." << std::endl;
				}

				this->editing_process();
			}

			if (standard_tag == true)
			{
				std::cout << std::endl;
				std::cout << "You added " << complete_string;
				std::cout << std::endl;

				outfile << this->complete_string;
			}
			else
			{
				std::cout << std::endl;
				std::cout << "You added " << complete_hyperlink;
				std::cout << std::endl;

				outfile << this->complete_hyperlink;
			}

			// File always writes the data when finished.
			*global_point += 1;

			this->local_hyperlink.clear();
			this->tag_grab.clear();
			this->complete_hyperlink.clear();

			// Create a standardized function that can be used for most of the other tags. TODO

		}
		else if (this->option == 'n')
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

	std::cout << "All done with tagging! Finishing document cleanup..." << std::endl;

	std::cout << "Writing body end tag..." << std::endl;
	std::cout << std::endl;
	std::cout << "</body>" << std::endl;

	outfile << std::endl;
	outfile << "</body>" << std::endl;

	// This runs when the program is finished tagging.
	std::cout << "Writing HTML end tag..." << std::endl;
	std::cout << std::endl;
	std::cout << "</html>" << std::endl;

	outfile << std::endl;
	outfile << "</html>"; // Root HTML tag is closed. Always.

	*global_point = *global_point + 2; // For debugging purposes.

	std::cout << std::endl;
	std::cout << "Lines wrapped up at " << find_line() << ".";
	std::cout << std::endl;

	outfile.close(); // ALWAYS close the file
};

void Page::page_explain()
{
	std::cout << "When you are finished, a matching </body> tag will be added to the end of the document." << std::endl;
	std::cout << "The </html> tag will also be added automatically." << std::endl;
	std::cout << "This will make it possible for the page to be visible in a web browser." << std::endl;
	std::cout << std::endl;
	std::cout << "The program will pause here to give you a minute to catch up." << std::endl;
	system("pause"); // Give the user a chance to read what's going on.
};

bool Page::create_file()
{
	extern std::string full_file;

	// fflush(stdin);
	// fflush(stdout);
	// std::cout << "Cleaning the file buffer..." << std::endl;

	std::cout << "Please enter the name of the file you are trying to create." << std::endl;
	std::cout << "Filename: ";
	std::cin >> this->f_name;
	std::cout << std::endl;

	// String is concatenated so that the file is valid.
	full_file = this->f_name + this->filetype;

	this->f_name = full_file;

	/* Not only is this the name of the file that will be created, this is the file name that will stay in memory.
	As long as the class remains active in the user session, full_file should not change unless the user calls for it to be closed. */

	if(std::ifstream(this->f_name))
	{
		std::cout << "File already exists!" << std::endl;
		std::cout << "Could not create file." << std::endl;

		return false;
	}
	std::ofstream file(this->f_name);

	if(!file)
	{
		std::cout << "An error occured and the file could not be created." << std::endl;

		return false;
	}

	this->declare(full_file);

	file.close(); // Always close the file when you're done with it.
	return true;
};