jira_analysis
=============

seriesArr - an array made up of selected issue statuses with a nested array for each issue
````php
Array
(
    [0] => stdClass Object
        (
            [name] => 'Slated'
            [data] => Array
                (
                    [0] => 7.27722222222
                    [1] => 0.292476851852
                    [2] => 8.02373842593
                    [3] => 0.00126157407407
                    [4] => 3.77528935185
                    [5] => 5.49678240741
                )

        )

    [1] => stdClass Object
        (
            [name] => 'Development in Progress'
            [data] => Array
                (
                    [0] => 18.0575694444
                    [1] => 2.84699074074
                    [2] => 0.238784722222
                    [3] => 5.06553240741
                    [4] => 0.232800925926
                    [5] => 11.8595138889

                )

        )

    [2] => stdClass Object
        (
            [name] => 'Queued for Code Review'
            [data] => Array
                (
                    [0] => 0
                    [1] => 0
                    [2] => 0
                    [3] => 9.95548611111
                    [4] => 0
                    [5] => 2.3141515661
                )
        )
)
````

ganttArr - an array made up of objects that correspond to statuses. The objects contain arrays of objects that correspond to particular issues (denoted by X) and their in/out times.
Color can be specified for each status so that it remains constant across various reports.

````php
Array (
    [0] => stdClass Object
        (
            [name] => 'Slated'
            [data] => Array
                (
                    [0] => stdClass Object
                        (
                            [x] => 0
                            [high] => 1377294121000
                            [low] => 1377022139000
                        )

                    [1] => stdClass Object
                        (
                            [x] => 0
                            [high] => 1377294139000
                            [low] => 1377294124000
                        )

                    [2] => stdClass Object
                        (
                            [x] => 0
                            [high] => 1377294420000
                            [low] => 1377294360000
                        )

                    [3] => stdClass Object
                        (
                            [x] => 1
                            [high] => 1377611918000
                            [low] => 1377526605000
                        )

                    [4] => stdClass Object
                        (
                            [x] => 2
                            [high] => 1377624758000
                            [low] => 1377619026000
                        )



                )

            [color] => '#2f7ed8'
        )

    [1] => stdClass Object
        (
            [name] => 'Development in Progress'
            [data] => Array
                (
                    [0] => stdClass Object
                        (
                            [x] => 0
                            [high] => 1377294124000
                            [low] => 1377294121000
                        )

                    [1] => stdClass Object
                        (
                            [x] => 0
                            [high] => 1377294360000
                            [low] => 1377294139000
                        )

                    [2] => stdClass Object
                        (
                            [x] => 0
                            [high] => 1377639030000
                            [low] => 1377294420000
                        )

                    [3] => stdClass Object
                        (
                            [x] => 2
                            [high] => 1378218237000
                            [low] => 1377624758000
                        )

                    [4] => stdClass Object
                        (
                            [x] => 5
                            [high] => 1377875755000
                            [low] => 1377623242000
                        )

                )

            [color] => '#0d233a'
        )

)
````