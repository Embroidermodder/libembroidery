# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'The Embroidermodder Project'
copyright = '2013-2024, The Embroidermodder Team'
author = 'The Embroidermodder Team'
release = '2.0.0-alpha4'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    "sphinx.ext.todo",
    "sphinx.ext.coverage",
    "sphinx.ext.viewcode"
]

templates_path = ['_templates']
exclude_patterns = []

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_title = "Embroidermodder"
html_theme = 'nature'
"""
html_theme = 'sphinx_book_theme'
html_theme_options = {
    "announcement": "IN ALPHA DEVELOPMENT, NOT READY FOR SERIOUS USE",
    "toc_title": "Contents",
    "navbar_end": [
        "index.html",
        "emrm.html",
        "em_user.html",
        "api/html/index.html",
        "mobile_user.html",
        "pet_user.html"
    ],
    "repository_provider": "github",
    "repository_url": "https://github.com/embroidermodder/libembroidery",

    "use_download_button": True,
    "use_repository_button": True,
    "use_source_button": True,
    "use_edit_page_button": True,
    "use_fullscreen_button": True,

    "home_page_in_toc": True,
    "show_navbar_depth": 3,
    "max_navbar_depth": 4,
    "navigation_with_keys": False
}
"""
html_static_path = ['_static']
# html_css_files = ["custom.css"]
html_logo = "docs/images/icons/app.png"

# -- Options for LaTeX output -------------------------------------------------
