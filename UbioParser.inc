<?php

/**
 * Parses Ubio RSS Feeds.
 */
class UbioParser extends FeedsParser {

  /**
   * Parses a raw string and populates FeedsImportBatch object from it.
   */
  public function parse(FeedsImportBatch $batch, FeedsSource $source) {


    // Load the parser library.
    require_once(drupal_get_path('module', 'mblwhoi_ubio_feeds_parser') . '/mblwhoi_ubio_feeds_parser.inc');

    // Get the file's content.
    $string = $batch->getRaw();

    // Parse it.
    $items = parse_ubio_rss($string);

    // Populate the FeedsImportBatch object with the parsed results.
    $batch->title = 'uBio Feed';
    $batch->items = $items;
  }

  public function getMappingSources() {


      $item['article_title'] = $title;
      $item['article_url'] = $link;
      $item['abstract'] = $description;
      $item['image'] = $image;
      $item['image_name'] = $image_name;
      $item['source_title'] = $sourceTITLE;
      $item['source_url'] = $sourceURL;


    return array(
                 'article_title' => array(
                                  'name' => t('Article Title'),
                                  'description' => t('Article Title'),
                                  ),
                 'article_url' => array(
                                  'name' => t('Article URL'),
                                  'description' => t('Article URL'),
                                  ),

                 'abstract' => array(
                                  'name' => t('Abstract'),
                                  'description' => t('Abstract'),
                                 ),

                 'image_url' => array(
                                  'name' => t('Image URL'),
                                  'description' => t('Image URL'),
                                 ),

                 'image_name' => array(
                                  'name' => t('Image Name'),
                                  'description' => t('Image Name'),
                                 ),

                 'journal_title' => array(
                                  'name' => t('Journal Title'),
                                  'description' => t('Journal Title'),
                                 ),

                 'journal_url' => array(
                                  'name' => t('Journal URL'),
                                  'description' => t('Journal URL'),
                                 )
                 );

  }

  }
?>