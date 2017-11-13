<?php

$description = "Streamlining dead memes since 2016. Refresh the page to become a professional shitposter.";
$image = "http://gash.ca/guys/header.png";
$title = "Shitpost Generator";

?>
<head>
<title>Shitpost Generator</title>
<meta property="og:image" content="<?php echo $image; ?>" />
<meta property="og:title" content="<?php echo $title; ?>" />
<meta property="og:url" content="http://gash.ca/guys/" />
<meta property="og:description" content="<?php echo $description; ?>" />
<meta property="og:site_name" content="Chris Bush's Cool Website" />
<meta property="twitter:card" content="summary" />
<meta property="twitter:site" content="@starchfacts" />
<meta property="twitter:creator" content="@starchfacts" />
<meta property="twitter:description" content="<?php echo $description; ?>" />
<meta property="twitter:title" content="<?php echo $title; ?>" />

</head>
<body style="margin:0px;width:100%;height:100%" >
<?php

$blob64 = exec("../../guys/make_image");

?>
<center>
<h1><a href="?browserHistoryToken=<?php echo substr(md5(microtime()), 0, 6); ?>" >Roll again</a></h1>
<a href="data:image/png;base64,<?php echo $blob64; ?>" >
<img style="max-height:90%;width:auto" src="data:image/png;base64,<?php echo $blob64; ?>" />
</a>
<br /><br />
</center>
<p style="color:#888;margin:10pt;font-size:10pt;">random images from <a href="https://frinkiac.com/" target=".">frinkiac</a><br />
let's say inspired by
<a href="https://www.facebook.com/groups/shitpostingsimpsons" target="." >simpsons shitposting</a><br />
generator by <a href="https://twitter.com/starchfacts" target="." >@starchfacts</a><br />
fork me on <a href="https://github.com/crust/shitpostgen" target="." >github</a><br/>
</p>
