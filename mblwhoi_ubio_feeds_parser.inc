<?php

/**
 * Parser for uBio RSS feed.
 */


/**
 * parse_ubio_rss
 * Takes ubio rss xml string.
 * Returns an array of parsed items from a uBio RSS feed.
 */

function parse_ubio_rss($xml){

  $xml = preg_replace("/(\n|\r|\t)/","",$xml);
  $contents = preg_split("/<item[^s]/",$xml);

  $items = array();

  while(list($key,$val)=each($contents)){
    if($key!=0){

      $item = array();

      $title="";
      $link="";
      $description="";
      $image="";
      $image_name="";

      if(preg_match("/<link>(.*)<\/item>/",$val,$arr)) $link = trim($arr[1]);
      if(preg_match("/^(.*)<\/link>/",$link,$arr)) $link = trim($arr[1]);
      if(preg_match("/^<!\[CDATA\[\[[^\]]*\](.*)\]\]>$/",$link,$arr)) $link = $arr[1];
      if(preg_match("/^<!\[CDATA/",$link,$arr))
				{
					$link = str_replace("<![CDATA[","",$link);
					$link = str_replace("]]>","",$link);
				}

      if(preg_match("/<title>(.*)<\/item>/",$val,$arr)) $title = trim($arr[1]);
      if(preg_match("/^(.*)<\/title>/",$title,$arr)) $title = trim($arr[1]);
      if(preg_match("/^<!\[CDATA\[\[[^\]]*\](.*)\]\]>$/",$title,$arr)) $title = $arr[1];
      if(preg_match("/^<!\[CDATA/",$title,$arr))
				{
					$title = str_replace("<![CDATA[","",$title);
					$title = str_replace("]]>","",$title);
				}

      if(preg_match("/<source url=\"([^\"]*)\">(.*)<\/item>/",$val,$arr))
				{
					$sourceURL = trim($arr[1]);
					$sourceTITLE = trim($arr[2]);
					if(preg_match("/^(.*)<\/source>/",$sourceTITLE,$arr)) $sourceTITLE = trim($arr[1]);
					if(preg_match("/^Latest Issue of (.*)$/",$sourceTITLE,$arr)) $sourceTITLE=$arr[1];
					if(preg_match("/^(.*) - Latest articles$/",$sourceTITLE,$arr)) $sourceTITLE=$arr[1];
				}

      if(preg_match("/<enclosure url=\"([^\"]*)\"/",$val,$arr))
				{
					$image = $arr[1];
					if(preg_match("/\/([^\/]*)\.png/",$image,$arr)) $image_name=str_replace("_"," ",$arr[1]);
				}


      $item['article_title'] = $title;
      $item['article_url'] = $link;
      $item['abstract'] = $description;
      $item['image_url'] = $image;
      $item['image_name'] = $image_name;
      $item['journal_title'] = $sourceTITLE;
      $item['journal_url'] = $sourceURL;


      // Decode html entitities.
      foreach ($item as $k => $v){
        $item[$k] = html_entity_decode($v, ENT_QUOTES,'utf-8');
      }


      $items[] = $item;
    }
  }

  return $items;
}

?>