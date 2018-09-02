const char* MainPageHtml1 = R"-----(
<!DOCTYPE html>

<html>
<head>
    <meta charset="utf-8" />
    <title>Landscape Controller Main</title>
</head>
<body>
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
<a href="/command?r=umbrella&a=toggle">Toggle</a>
</p>

<h1>Setup</h1>

<h3><a href="/Provision">Controller Setup</a></h3>


)-----";

// PROVISIONING PAGE

const char* ProvisionPageHtml1 = R"-----(
<!DOCTYPE html>

<html>
<head>
    <meta charset="utf-8" />
    <title>EagleDecorations Setup</title>
</head>
<body>
    <h1>EagleDecorations Controller Setup</h1>

        <h3><a href="/">Main Page</a></h3>


)-----";

const char* ProvisionPageHtml2 = R"-----(

    <h1>Wireless Provisioning</h1>
<p>
    Chose a network from the list or enter one directly.
</p>
<h2>Visible Networks</h2>
<form>
    <select name="ssid">
)-----";

const char* ProvisionPageHtml3 = R"-----(
    </select>
    &nbsp;&nbsp; Password: <input type="text" name="password"/>
    <input type="submit" value="Register"/>
</form>
<h3>Other Network</h3>
<form>
    SSID: <input type="text" name="ssid" />
    &nbsp;&nbsp; Password: <input type="text" name="password"/>
    <input type="submit" value="Register"/>
</form>

</body>
</html>
)-----";


