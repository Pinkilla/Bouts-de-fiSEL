<?php
// $Id: user-profile-category.tpl.php,v 1.2 2007/08/07 08:39:36 goba Exp $

/**
 * @file user-profile-category.tpl.php
 * Default theme implementation to present profile categories (groups of
 * profile items).
 *
 * Categories are defined when configuring user profile fields for the site.
 * It can also be defined by modules. All profile items for a category will be
 * output through the $profile_items variable.
 *
 * @see user-profile-item.tpl.php
 *      where each profile item is rendered. It is implemented as a definition
 *      list by default.
 * @see user-profile.tpl.php
 *      where all items and categories are collected and printed out.
 *
 * Available variables:
 * - $title: Category title for the group of items.
 * - $profile_items: All the items for the group rendered through
 *   user-profile-item.tpl.php.
 * - $attributes: HTML attributes. Usually renders classes.
 *
 * @see template_preprocess_user_profile_category()
 */
?>
<?php if ($title) : ?>
<?php
    $str = $title;
    $str = htmlentities($str, ENT_NOQUOTES, 'utf-8');
    
    $str = preg_replace('#\&([A-za-z])(?:acute|cedil|circ|grave|ring|tilde|uml)\;#', '\1', $str);
    $str = preg_replace('#\&([A-za-z]{2})(?:lig)\;#', '\1', $str); // pour les ligatures e.g. '&oelig;'
    $str = preg_replace('#\&[^;]+\;#', '', $str); // supprime les autres caractères
?>

<div  id="profile_section_<?php print str_replace(" ", "_", $str); ?>">

  <h3><?php print $title; ?></h3>
<?php endif; ?>

<dl<?php print $attributes; ?>>
  <?php print $profile_items; ?>
</dl>
</div>