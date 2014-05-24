<?php

/**
 * Provide user information for logging.
 *
 * @param array $user
 */
function hook_raven_user_alter(&$user) {
  global $user;
  if (user_is_logged_in()) {
    $variables['id'] = $user->uid;
    $variables['name'] = $user->name;
    $variables['email'] = $user->mail;
    $variables['roles'] = implode(', ', $user->roles);
  }
}

/**
 * Provide tags for logging.
 *
 * @param array $tags
 */
function hook_raven_tags_alter(&$tags) {
  // todo: example
}

/**
 * Provide extra information for logging.
 *
 * @param array $extra
 */
function hook_raven_extra_alter(&$extra) {
  // todo: example
}

/**
 * Filter php errors.
 *
 * @param array $error
 */
function hook_raven_error_filter_alter(&$error) {
  $known_errors = array();

  drupal_alter('raven_known_php_errors', $known_errors);

  // Filter known errors to prevent spamming the Sentry server.
  foreach ($known_errors as $known_error) {
    $check = TRUE;

    foreach ($known_error as $key => $value) {
      if ($error[$key] != $value) {
        $check = FALSE;
        break;
      }
    }

    if ($check) {
      $error['process'] = FALSE;
      break;
    }
  }
}

/**
 * Provide the list of known php errors.
 *
 * @param array $known_errors
 */
function hook_raven_known_php_errors_alter(&$known_errors) {
  $known_errors[] = array(
    'code' => E_NOTICE,
    'message' => 'Array to string conversion',
    'file' => DRUPAL_ROOT . '/sites/all/modules/views/plugins/views_plugin_cache.inc',
    'line' => 206,
  );

  $known_errors[] = array(
    'code' => E_NOTICE,
    'message' => 'Undefined index: width',
    'file' => DRUPAL_ROOT . '/sites/all/modules/flexslider/flexslider_fields/flexslider_fields.module',
    'line' => 140,
  );

  $known_errors[] = array(
    'code' => E_NOTICE,
    'message' => 'Undefined index: height',
    'file' => DRUPAL_ROOT . '/sites/all/modules/flexslider/flexslider_fields/flexslider_fields.module',
    'line' => 141,
  );
}

/**
 * Filter watchdog messages.
 *
 * @param array $filter
 */
function hook_raven_watchdog_filter_alter(&$filter) {
  // todo: example
}