<?php
// $Id: block.tpl.php,v 1.7 2010/01/20 11:19:34 ktleow Exp $
?>
<div id="block-<?php print $block->module .'-'. $block->delta; ?>" class="<?php print 'block block-' . $block->module . ' block-' . $block_id . ' block-' . $block->extraclass . ' block-' . $block_id . '-' . $block->extraclass; ?>">
  <div class="block-tl"><div class="block-tr"><div class="block-br"><div class="block-bl"><div class="block-content">
    <?php if ($block->subject): ?>
      <div class="block-subject"><div class="block-subject-tl"><div class="block-subject-tr"><div class="block-subject-br"><div class="block-subject-bl"><div class="block-subject-content">
        <h2><?php print $block->subject; ?></h2>
      </div></div></div></div></div></div>
    <?php endif;?>
    <div class="clear-both"><!-- --></div>

    <div class="block-content-content content">
      <?php print $block->content; ?>
    </div>
  </div></div></div></div></div>
</div>
<div class="clear-both"><!-- --></div>
