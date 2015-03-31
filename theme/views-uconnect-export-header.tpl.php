<?php print '<?xml version="1.0" encoding="utf-8" ?>'."\n"; ?>
<!DOCTYPE Repository [
<!ENTITY rsquo   "'">
<!ENTITY oacute   "ó">
<!ENTITY aacute   "á">
<!ENTITY ntilde   "ñ">
<!ENTITY uacute   "ú">
<!ENTITY iacute   "í">
<!ENTITY eacute   "é">
]>

<Repository xmlns="http://www.openarchives.org/OAI/2.0/static-repository" 
            xmlns:oai="http://www.openarchives.org/OAI/2.0/" 
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
            xsi:schemaLocation="http://www.openarchives.org/OAI/2.0/static-repository 
                                http://www.openarchives.org/OAI/2.0/static-repository.xsd">
 <Identify>
    <!-- Fill out as appropriate: repositoryName, baseURL, adminEmail -->
    <oai:repositoryName><?php print $repository_name; ?></oai:repositoryName>
    <oai:baseURL><?php print $base_url; ?></oai:baseURL>
    <oai:protocolVersion><?php print $protocol_version; ?></oai:protocolVersion>
    <oai:adminEmail><?php print $admin_email; ?></oai:adminEmail>
    <oai:earliestDatestamp><?php print $earliest_timestamp; ?></oai:earliestDatestamp>
    <oai:deletedRecord><?php print $deleted_record; ?></oai:deletedRecord>
    <oai:granularity><?php print $granularity; ?></oai:granularity>
  </Identify>
  <ListMetadataFormats>
    <oai:metadataFormat>
      <oai:metadataPrefix><?php print $oai_metadata_prefix; ?></oai:metadataPrefix>
      <oai:schema><?php print $oai_schema; ?></oai:schema>
      <oai:metadataNamespace><?php print $oai_metadata_namespace; ?></oai:metadataNamespace>
    </oai:metadataFormat>
  </ListMetadataFormats>
  <ListRecords metadataPrefix="<?php print $oai_metadata_prefix; ?>">