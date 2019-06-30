const char* MainPageHtml1 = R"-----(
<!DOCTYPE html>

<html>
<head>
    <meta charset="utf-8" />
    <title>Landscape Controller Main</title>
</head>
<body>
    <font size="+3">
    <h1>Landscape Controller</h1>

    <h1>Status</h1>
    <p>
)-----";


const char* MainPageHtml2 = R"-----(
</p>
<h1>Control</h1>

<p><b>Pump</b><br/>
<a href="/command?r=pump&a=on">On</a><br/>
<a href="/command?r=pump&a=off">Off</a><br/>
<a href="/command?r=pump&a=toggle">Toggle</a>
</p>

<p><b>Bed lights</b><br/>
<a href="/command?r=bed&a=on">On</a><br/>
<a href="/command?r=bed&a=off">Off</a><br/>
<a href="/command?r=bed&a=toggle">Toggle</a>
</p>

<p><b>House lights</b><br/>
<a href="/command?r=house&a=on">On</a><br/>
<a href="/command?r=house&a=off">Off</a><br/>
<a href="/command?r=house&a=toggle">Toggle</a>
</p>

<p><b>Umbrella lights</b><br/>
<a href="/command?r=umbrella&a=on">On</a><br/>
<a href="/command?r=umbrella&a=off">Off</a><br/>
<a href="/command?r=umbrella&a=toggle">Toggle</a><br/>
<a href="/command?r=umbrella&a=dim20">20%</a>&nbsp;&nbsp;
<a href="/command?r=umbrella&a=dim40">40%</a>&nbsp;&nbsp;
<a href="/command?r=umbrella&a=dim60">60%</a>&nbsp;&nbsp;
<a href="/command?r=umbrella&a=dim80">80%</a>&nbsp;&nbsp;
<a href="/command?r=umbrella&a=dim100">100%</a>
</p>

<p><b>All lights</b><br/>
<a href="/command?r=lights&a=on">On</a><br/>
<a href="/command?r=lights&a=off">Off</a><br/>
<a href="/command?r=lights&a=toggle">Toggle</a>
</p>

)-----";
