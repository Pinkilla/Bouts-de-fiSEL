<?php
// $Id: box.tpl.php,v 1.5 2010/01/20 11:19:34 ktleow Exp $
?>
<div class="box">
  <div class="box-tl"><div class="box-tr"><div class="box-br"><div class="box-bl"><div class="box-content">
    <?php if ($title): ?>
      <h2><?php print $title; ?></h2>
    <?php endif; ?>

    <div class="content">
      <?php print $content; ?>
    </div>
  </div></div></div></div></div>
</div>
