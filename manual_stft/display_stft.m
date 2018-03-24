function display_stft (filename)
    spect = textread (filename); %#ok<DTXTRD>
    sz = size(spect, 2);
    spect = spect(:,floor( sz/2:sz));
    imagesc (log(spect'));
endhttps://www.hodinkee.com/articles/the-glycine-airman-no-1