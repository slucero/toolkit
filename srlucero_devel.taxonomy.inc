<?php
/**
 * @file
 * Taxonomy funcitonality for the toolkit.
 */

/**
 * Custom function to load an array of terms into a specified vocabulary.
 */
function _srlucero_devel_taxonomy_terms_load_terms($terms, $vocab_name){
  $vocab = taxonomy_vocabulary_machine_name_load($vocab_name);
  if ($vocab == false) {
    drupal_set_message('Error while attempting to install vocabulary ' . $vocab_name, 'error');
  }
  else {
    foreach($terms as $weight => $term){
      $data = new stdClass();
      $data->name = $term;
      $data->vid = $vocab->vid;
      $data->weight = $weight;

      taxonomy_term_save($data);
    }
  }
}
