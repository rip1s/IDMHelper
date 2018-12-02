# IDMHelper
Make your Internet Download Manager more powerful!

Initially I was stuck at changing IDM's user-agent, I'm surprise that didn't find any options in IDM interface that I can do that (Correct me if I'm wrong), so I create a simple program to do this stuff.

## Usage
```
C:\>IDMHelper.exe -h
IDM Download helper by @unamer(https://github.com/unamer)

Usage:  idmhelpr.exe <Option1> <Option2>...

Available options:
        -u: your target url <Required>
        -a: your user-agent
        -c: your cookies
        -d: your post data
        -r: your referer
        -U: your username
        -P: your password
        -o: your download path (where your files will be downloaded)
        -s: your download file name
        -f: download without any confirmations
        -q: do not download, insert to queue only
Example:

        idmhelper.exe -u https://www.google.com/ -a "What ever ua" -c "my cookies" -f
```

## Reference

* http://www.internetdownloadmanager.com/support/idm_api.html
