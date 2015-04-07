Views UCARConnect Export
=====================

## Introduction

The UCARConnect Export views plugin module is a Drupal 7 plugin for Views that provides a formatted XML output of site content that conforms to the NSDL LAR schema necessary for static repository ingest into the UCARConnect Learning Resource Catalog.
Also provides a custom views input field for License information (if needed).

## Requirements

This module requires Views as well as the following modules/libraries:

[UCARConnect] (https://github.com/UCAR/uconnect)

Several input field modules are available with special handling and formatting necessary for the UCARConnect repository

[UCARConnect ASN Standard] (https://github.com/UCAR/field_uconnect_asn_standard)

[UCARConnect Education Level] (https://github.com/UCAR/field_uconnect_education_level)

[UCARConnect License] (https://github.com/UCAR/field_uconnect_license)

[UCARConnect Partner Subject] (https://github.com/UCAR/field_uconnect_partner_subject)

[UCARConnect Resource Type] (https://github.com/UCAR/field_uconnect_resource_type)

[UCARConnect Subject] (https://github.com/UCAR/field_uconnect_subject)

## Installation

Install as usual via the Drupal admin modules screen.

## Configuration

To create a view using the UCARConnect Export format

1. Go to Admin > Structure > Views
2. Select 'add new view' 
3. Provide a View name for your new view and deselect 'Create a page'
4. Click 'Continue and edit'
5. Click the 'Add' button and select 'UCARConnect Export'
6. Under 'Page Settings' click 'No path is set' and define the relative URL your XML output should be viewed at
7. Under 'Format' click 'Settings' next to Learning Application Ready (lar) and provide a name for your repository, a prefix for your records, and a prefix for your resource IDs.  
8. Select your filters and fields as you normally would for a Views display. *
9. After selecting your fields, under 'Format' click 'Settings' next to Lar Fields and assign a LAR Element Name to each Drupal Field Label.

*Note: Fields must be organized in a specific order to conform to the NSDL LAR Schema.  Some items need additional attributes and you may need to add custom inputs to cover all requirements. For more information on schema requirements, please see https://wiki.ucar.edu/display/UCARConnectDocs/Information+about+the+LAR+Metadata+Format

Example for field order:

* url/identifier
* title of resource
* description of resource
* subjects (repeating)
* language
* format
* education level (repeating)
* audienceRefinement
* type (repeating)
* date (repeating)
* contributor (repeating)
* accessRestrictions
* license

## Maintainers/Sponsors

Current maintainers:

* [Sharon Clark] (https://github.com/slclark)

## Version history

Version  | NOTES
------------- | -------------
7.x-1.1  | use custom field module for license rather than views field
