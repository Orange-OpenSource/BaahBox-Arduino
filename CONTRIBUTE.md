# How to contribute to this part of the project?


## Rule 0: Clean sources!

You should follow common C++ naming conventions so as to have a clean code.



## Rule 1: Use smartly Git branches

You should use feature branches for your work.
A common usage is to create a branch from the _dev_ branch for your feature, work on it, and once the job is done and the app is both building and running, merge to the _dev_ branch using a pull request.

Once the _dev_ branch is enough enriched, you should make a merge from _dev_ to _master_ so as to keep a strong, tested, building, running and well-working version of the sources.

Do not forget to squash commits.

Feel free to get more details about Gitflow workflow here: https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow



## Rule 2: Write clear commit messages

So as to be notified of each commit and brought evolutions, you should format your commit messages following a clear and simple pattern.

For example:
```shell
git commit -s -m "chore: #3 - I dislike pineapples"
```

The first item can be choosen within "chore", "feat", "fix", "test", "doc", "refactor" or "style".
Before the "-" symoble we can refer the issue or card we work on on.
After the "-" we can add more details.
Keep in mind commit messages should be quite short (~ 80 characters length), you can add more details with line breaks.

For example:
```shell
git commit -s -m $'chore: #3 - I dislike pineapples\n\nLorem ipsum foo bar wizz berlingots...'
```

Keep in mind your commit message has a title (~ 80 characters length) and a body (after the \n\n) where more details can be added.

Feel free to have a look on this link: https://gist.github.com/stephenparish/9941e89d80e2bc58a153. You can also use a GUI-based tool for your commis, but keep them clear and follow the same principles.



## Rule 3: Use pull requests

Once you have choosen an issue to work on, you should create a "Work In Progress" pull request prefixed by "WIP:". Thus you will have always a look on the state of your evolutions and your colleagues will be able to know on which things you work on. So as to update the _dev_ and _master_ branches, you have to make such pull requests. Thus you can ask colleagues for help so as to double-check your source code and be sure you won't break anything. These branches can be push-protected.



## Rule 4: Tags and versions

Once we are sure a version of the sources and the app builds and runs correctly without bugs, we have to tag it with the version number. Thus we ensure to keep versions of working sources. For version number _X.Y.Z._, the _X_ refers to the major update, the _Y_ to a minor update, and the _Z_ to the bug fix.  



