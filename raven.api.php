<?php

/**
 * Provide user information for logging.
 *
 * @param array $user_info
 *   A reference to array of user account info.
 */
function hook_raven_user_alter(array &$user_info) {
  global $user;
  if (user_is_logged_in()) {
    $user_info['id'] = $user->uid;
    $user_info['name'] = $user->name;
    $user_info['email'] = $user->mail;
    $user_info['roles'] = implode(', ', $user->roles);
  }
}

/**
 * Provide tags for logging.
 *
 * @param array $tags
 *   A reference to array of sentry tags.
 */
function hook_raven_tags_alter(array &$tags) {
  $tags['foo_version'] = get_foo_version();
}

/**
 * Provide extra information for logging.
 *
 * @param array $extra
 *   A reference to array of extra error info.
 */
function hook_raven_extra_alter(array &$extra) {
  $extra['foo'] = 'bar';
}

/**
 * Filter known errors so do not log them to Sentry again and again.
 *
 * @param array $error
 *   A reference to array contains error info.
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
 *   A reference to array contains php errors info.
 */
function hook_raven_known_php_errors_alter(array &$known_errors) {
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
 * Filter known watchdog entries so do not log them to Sentry again and again.
 *
 * @param array $filter
 *   A reference to array contains log entry info.
 */
function hook_raven_watchdog_filter_alter(array &$filter) {
  $log_entry = $filter['log_entry'];
  if ($log_entry['type'] === 'foo') {
    $filter['process'] = FALSE;
  }
}