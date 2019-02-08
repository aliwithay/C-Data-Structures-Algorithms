 #! /bin/bash
    if (($# != 2))
    then
        echo "Usage: ./rn .[EXTENSION] .[EXTENSION]" >&2
        exit 1
    elif
        old_suffix=$1
        new_suffix=$2
            
        for f in *.$old_suffix
        do
            new_name=${f%.*}.$new_suffix
            if [[-e $new_name]]
            then
                echo "A file with the name already exists."
                exit 2
            fi
            mv $f $new_name
            if [[$? != 0]]
            then
                echo "File cannot be renamed."
                exit 3
            fi
            echo Rename $f to $new_name
        done
    fi        
